#include <hardware/gpio.h>
#include <pico.h>
#include "keyboard_config.h"
#include <stdint.h>

void configure_keyboard() {
    for (int row_idx = 0; row_idx < N_ROWS; ++row_idx) {
        gpio_init(ROW_PINS[row_idx]);
        gpio_set_dir(ROW_PINS[row_idx], 0);
    }
    for (int col_idx = 0; col_idx < N_COLS; ++col_idx) {
        gpio_init(COL_PINS[col_idx]);
        gpio_set_dir(COL_PINS[col_idx], 1);
        gpio_pull_down(COL_PINS[col_idx]);
    }
}

