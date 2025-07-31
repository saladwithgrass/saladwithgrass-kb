#include "gpio_i2c.h"
#include "../gpio/gpio.h"
#include "../pads/pads.h"
#include "../../errors/errors.h"
#include <stddef.h>
#include <stdint.h>

void configure_I2C0() {
    // disable i2c0
    PUT32(I2C0_ENABLE, 0);
    /*
    uint32_t target_value = 0;

    // set mode to MASTER
    target_value |= 0x1;

    // set speed to standard
    target_value |= (I2C_CON_SPEED_STANDARD<<1);

    // master addressing is 7 bit by default

    // enabled restart condition
    target_value |= (1<<5);

    // disable slave
    target_value |= (1<<6);

    // in the end
    target_value = 0b0001100011;
    */
    PUT32(I2C0_CON, 0b0001100011);
    // enable I2C0
    PUT32(I2C0_ENABLE, 1);
    while (1)
        if (GET32(I2C0_ENABLE_STATUS) & 1) break;
}

void set_I2C0_TAR(uint32_t target_address) {
    PUT32(I2C0_TAR, target_address);
}

Error configure_pads_I2C0(uint32_t sda_pin, uint32_t scl_pin){
    uint32_t iter;

    /* this part may be a bit tricky
     * to write branchlessly, i decided to store 
     * comparison results in one variable
     * if sda pin is valid, then the LSB will be 1,
     * if scl pin is valid, then the second bit will be 0 
     */
    uint8_t both_are_valid = 0;
    for (iter = 0; iter < NUM_I2C0_WIRE_PINS; ++iter) {
        both_are_valid |= (sda_pin == I2C0_SDA_PINS[iter]);
        both_are_valid |= ((scl_pin == I2C0_SCL_PINS[iter]) << 1);
    }
    if (!both_are_valid) {
        return ERROR_BAD_ARGUMENTS;
    }
    /* from rp2040 docs:
     *
     * Each controller must connect its clock SCL and data SDA to one pair of GPIOs. 
     * The I2C standard requires that drivers drive
     *  a signal low, or when not driven the signal will be pulled high. 
     *  This applies to SCL and SDA. The GPIO pads should be
     * configured for:
     * • pull-up enabled
     * • slew rate limited
     * • schmitt trigger enabled
     */ 
    pads_enable_pullup(sda_pin);
    pads_enable_pullup(scl_pin);
    pads_disable_fast_slewrate(sda_pin);
    pads_disable_fast_slewrate(scl_pin);
    pads_enable_schmidt(sda_pin);
    pads_enable_schmidt(scl_pin);

    return ERROR_OK;
}

Error configure_pins_I2C0(uint32_t sda_pin, uint32_t scl_pin) {
    uint32_t iter;

    /* this part may be a bit tricky
     * to write branchlessly, i decided to store 
     * comparison results in one variable
     * if sda pin is valid, then the LSB will be 1,
     * if scl pin is valid, then the second bit will be 0 
     */
    uint8_t both_are_valid = 0;
    for (iter = 0; iter < NUM_I2C0_WIRE_PINS; ++iter) {
        both_are_valid |= (sda_pin == I2C0_SDA_PINS[iter]);
        both_are_valid |= ((scl_pin == I2C0_SCL_PINS[iter]) << 1);
    }
    if (!both_are_valid) {
        return ERROR_BAD_ARGUMENTS;
    }

    // disable output
    PUT32(SIO_GPIO_OUT_CLR, (1<<sda_pin) | (1<<scl_pin));
    PUT32(SIO_GPIO_OE_CLR, (1<<sda_pin) | (1<<scl_pin));

    // set function to I2C
    PUT32(IO_BANK0_GPIO_CTRL_RW(sda_pin), FUNCTION_I2C_SDA);
    PUT32(IO_BANK0_GPIO_CTRL_RW(scl_pin), FUNCTION_I2C_SCL);

    return ERROR_OK;
}

Error write_byte_i2c(uint32_t target_address, uint8_t msg) {
    // check if I2C is running
    if (!(GET32(I2C0_ENABLE_STATUS) & 1))
        return ERROR_HARDWARE_MISCONFIGURATION;
    set_I2C0_TAR(target_address);
    PUT32(I2C0_DATA_CMD, msg | (1<<9));
    while (GET32(I2C0_TXFLR) & 1) {}
    return ERROR_OK;
}

Error write_bytearray_i2c(uint32_t target_address, uint8_t *msg, size_t msg_len) {
    if (!(GET32(I2C0_ENABLE_STATUS) & 1))
        return ERROR_HARDWARE_MISCONFIGURATION;
    set_I2C0_TAR(target_address);
    for (size_t iter = 0; iter < msg_len; ++iter) {
        PUT32(I2C0_DATA_CMD, msg[iter] | (1<<9));
        while (GET32(I2C0_TXFLR) & 1) {}

    }
    
}

uint8_t slave_address_available(uint8_t addr) {
    // Clear any previous aborts
    PUT32(I2C0_CLR_TX_ABRT, 1);
    
    // Send START + address (write)
    PUT32(I2C0_DATA_CMD, (addr << 1) & 0xFE); // 7-bit address + write bit (0)

    // Wait for transmission to complete (TX_EMPTY)
    uint32_t timeout = 10000;
    while (--timeout)
        if (GET32(I2C0_RAW_INTR_STAT) & (1<<5)) break;

    if (timeout == 0) return 0; // Timeout error

    // Check for NACK (no ACK from slave)
    uint32_t abort_source = GET32(I2C0_TX_ABRT_SOURCE);
    
    // Clear abort source
    PUT32(I2C0_CLR_TX_ABRT, 1);
    
    // ABRT_TXDATA_NOACK = Bit 3 (0x08)
    return !(abort_source & 0x08);
}
