#ifndef I2C_LED_H_
#define I2C_LED_H_

#include "../RP2040/RP2040.h"
#include <stdint.h>

uint8_t pcf_state = 0x08; // P7=Backlight (1=on), P5=RW=0 (write)

// Update PCF8574 (sends current pcf_state to I2C)
void pcf_update() {
    i2c_start_write();
    i2c_write_byte(pcf_state);
    i2c_stop();
    delay_us(100); // Critical for stability
}

#endif // !I2C_LED_H_
