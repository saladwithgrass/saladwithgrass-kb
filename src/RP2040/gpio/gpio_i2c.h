#ifndef GPIO_I2C_H_
#define GPIO_I2C_H_

#include "gpio.h"
#include "../../errors/errors.h"
#include <stddef.h>
#include <stdint.h>

void configure_I2C0( void );
void set_I2C0_TAR( uint32_t target_address);

Error write_bytearray_i2c(uint32_t target_address, uint8_t* msg, size_t msg_len);
Error write_byte_i2c(uint32_t target_address, uint8_t msg);

Error configure_pads_I2C0(uint32_t sda_pin, uint32_t scl_pin);
Error configure_pads_I2C1(uint32_t sda_pin, uint32_t scl_pin);

Error configure_pins_I2C0(uint32_t sda_pin, uint32_t scl_pin);
Error configure_pins_I2C1(uint32_t sda_pin, uint32_t scl_pin);

uint8_t slave_address_available(uint8_t addr);
void scan_addresses();

#define NUM_I2C0_WIRE_PINS 8
const uint32_t I2C0_SDA_PINS[NUM_I2C0_WIRE_PINS] = {
    0, 4, 8, 12, 16, 20, 24, 28
};
const uint32_t I2C0_SCL_PINS[NUM_I2C0_WIRE_PINS] = {
    1, 5, 9, 13, 17, 21, 25, 29
};

#define NUM_I2C1_WIRE_PINS 7
const uint32_t I2C1_SDA_PINS[NUM_I2C1_WIRE_PINS] = {
    2, 6, 10, 14, 18, 22, 26
};
const uint32_t I2C1_SCL_PINS[NUM_I2C1_WIRE_PINS] = {
    3, 7, 11, 15, 19, 23, 27
};

#define I2C0_BASE               0x40044000

#define I2C0_CON                I2C0_BASE           // control register 
#define I2C0_TAR                (I2C0_BASE + 0x04)  // target address register
#define I2C0_SAR                (I2C0_BASE + 0x08)  // slave address register(in slave mode)
#define I2C0_DATA_CMD           (I2C0_BASE + 0x08)  // data buffer and command

#define I2C0_SS_SCL_HCNT        (I2C0_BASE + 0x14)  // Standard Speed I2C Clock SCL High Count Register
#define I2C0_SS_SCL_LCNT        (I2C0_BASE + 0x18)  // Standard Speed I2C Clock SCL Low Count Register
#define I2C0_FS_SCL_HCNT        (I2C0_BASE + 0x1c)  // Fast Mode or Fast Mode Plus SCL High Count Register
#define I2C0_FS_SCL_LCNT        (I2C0_BASE + 0x20)  // Fast Mode or Fast Mode Plus SCL Low Count Register
#define I2C0_INTR_STAT          (I2C0_BASE + 0x2c)  // I2C Interrupt Status Register
#define I2C0_INTR_MASK          (I2C0_BASE + 0x30)  // I2C Interrupt Mask Register
#define I2C0_RAW_INTR_STAT      (I2C0_BASE + 0x34)  // I2C Raw Interrupt Status Register
#define I2C0_RX_TL              (I2C0_BASE + 0x38)  // I2C Receive FIFO Threshold Register
#define I2C0_TX_TL              (I2C0_BASE + 0x3c)  // I2C Transmit FIFO Threshold Register
#define I2C0_CLR_INTR           (I2C0_BASE + 0x40)  // Clear Combined and Individual Interrupt Register
#define I2C0_CLR_RX_UNDER       (I2C0_BASE + 0x44)  // Clear RX_UNDER Interrupt Register
#define I2C0_CLR_RX_OVER        (I2C0_BASE + 0x48)  // Clear RX_OVER Interrupt Register
#define I2C0_CLR_TX_OVER        (I2C0_BASE + 0x4c)  // Clear TX_OVER Interrupt Register
#define I2C0_CLR_RD_REQ         (I2C0_BASE + 0x50)  // Clear RD_REQ Interrupt Register
#define I2C0_CLR_TX_ABRT        (I2C0_BASE + 0x54)  // Clear TX_ABRT Interrupt Register
#define I2C0_CLR_RX_DONE        (I2C0_BASE + 0x58)  // Clear RX_DONE Interrupt Register
#define I2C0_CLR_ACTIVITY       (I2C0_BASE + 0x5c)  // Clear ACTIVITY Interrupt Register
#define I2C0_CLR_STOP_DET       (I2C0_BASE + 0x60)  // Clear STOP_DET Interrupt Register
#define I2C0_CLR_START_DET      (I2C0_BASE + 0x64)  // Clear START_DET Interrupt Register
#define I2C0_CLR_GEN_CALL       (I2C0_BASE + 0x68)  // Clear GEN_CALL Interrupt Register
#define I2C0_ENABLE             (I2C0_BASE + 0x6c)  // I2C ENABLE Register
#define I2C0_STATUS             (I2C0_BASE + 0x70)  // I2C STATUS Register
#define I2C0_TXFLR              (I2C0_BASE + 0x74)  // I2C Transmit FIFO Level Register
#define I2C0_RXFLR              (I2C0_BASE + 0x78)  // I2C Receive FIFO Level Register
#define I2C0_SDA_HOLD           (I2C0_BASE + 0x7c)  // I2C SDA Hold Time Length Register
#define I2C0_TX_ABRT_SOURCE     (I2C0_BASE + 0x80)  // I2C Transmit Abort Source Register
#define I2C0_SLV_DATA_NACK_ONLY (I2C0_BASE + 0x84)  // Generate Slave Data NACK Register
#define I2C0_DMA_CR             (I2C0_BASE + 0x88)  // DMA Control Register
#define I2C0_DMA_TDLR           (I2C0_BASE + 0x8c)  // DMA Transmit Data Level Register
#define I2C0_DMA_RDLR           (I2C0_BASE + 0x90)  // DMA Transmit Data Level Register
#define I2C0_SDA_SETUP          (I2C0_BASE + 0x94)  // I2C SDA Setup Register
#define I2C0_ACK_GENERAL_CALL   (I2C0_BASE + 0x98)  // I2C ACK General Call Register
#define I2C0_ENABLE_STATUS      (I2C0_BASE + 0x9c)  // I2C Enable Status Register
#define I2C0_FS_SPKLEN          (I2C0_BASE + 0xa0)  // I2C SS, FS or FM+ spike suppression limit
#define I2C0_CLR_RESTART_DET    (I2C0_BASE + 0xa8)  // Clear RESTART_DET Interrupt Register
#define I2C0_COMP_PARAM_1       (I2C0_BASE + 0xf4)  // Component Parameter Register 1
#define I2C0_COMP_VERSION       (I2C0_BASE + 0xf8)  // I2C Component Version Register
#define I2C0_COMP_TYPE          (I2C0_BASE + 0xfc)  // I2C Component Type Register


#define I2C_CON_SPEED_STANDARD  0x1
#define I2C_CON_SPEED_FAST      0x2
#define I2C_CON_SPEED_HIGH      0x3

#endif // !GPIO_I2C_H_
