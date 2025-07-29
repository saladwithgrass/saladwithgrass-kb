#ifndef GPIO_I2C_H_
#define GPIO_I2C_H_

#include "stdint.h"
#include "gpio.h"
#include "../errors/errors.h"
#include <stdint.h>

Error configure_pads_I2C0(uint32_t sda_pin, uint32_t scl_pin);
Error configure_pads_I2C1(uint32_t sda_pin, uint32_t scl_pin);

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

#endif // !GPIO_I2C_H_
