#include "../RP2040/RP2040.h"
#include "i2c_lcd.h"
#include <stdint.h>

const uint32_t sda_pin = 12;
const uint32_t scl_pin = 10;

int lcd_i2c_run_test() {
    clock_init();
    init_IOBANK0();
    return 0;
}
