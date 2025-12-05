#include "pin_polling.h"
#include "keyboard_config.h"

#include <hardware/gpio.h>
#include <pico.h>
#include <pico/time.h>
#include <stddef.h>
#include <stdint.h>

extern const uint8_t ROW_PINS[N_ROWS];
extern const uint8_t COL_PINS[N_COLS];
extern const uint32_t US_PER_ROW;

static size_t last_added = 0;
static key_position registered_presses[MAX_CONCURRENT_KEYS];

void poll_row(uint8_t row) {
    uint32_t mask = 1 << row ;
    gpio_set_mask(mask);
    gpio_clr_mask(~mask);
    sleep_us(US_PER_ROW);
    for (int col_id = 0; col_id < N_COLS; ++col_id) {
        if (gpio_get(COL_PINS[col_id])) {
            register_press(row, COL_PINS[col_id]);
        }
    }
    gpio_clr_mask(~mask);
}

void poll_whole_kb() {
    for (int row_id = 0; row_id < N_ROWS; ++row_id) {
        poll_row(ROW_PINS[row_id]);
    }
}

void clear_presses() {
    last_added = 0;
}

void register_press(uint8_t row, uint8_t col) {
    // FIXME this is kind of ugly and there should be a more proper processing
    last_added %= MAX_CONCURRENT_KEYS;

    registered_presses[last_added].row = row;
    registered_presses[last_added].col = col;
    last_added++;
}

void poll_and_get_presses(key_position *result) {
    poll_whole_kb();
    for (size_t i = 0; i < MAX_CONCURRENT_KEYS; ++i) {
        result[i] = registered_presses[i];
    }
}

