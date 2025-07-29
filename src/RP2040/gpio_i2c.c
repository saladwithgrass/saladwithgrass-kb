#include "gpio_i2c.h"
#include <stdint.h>
#include "../errors/errors.h"

Error configure_pads_I2C0(uint32_t sda_pin, uint32_t scl_pin){
    uint32_t iter;

    /* this part may be a bit tricky
     * to write branchlessly, i decided to store 
     * comparison results in one variable
     * if sda pin is valid, then the LSB will be 1,
     * if scl pin is valid, then the second bit will be 0 
     */
    uint8_t both_are_valid;
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

    return ERROR_OK;
}
