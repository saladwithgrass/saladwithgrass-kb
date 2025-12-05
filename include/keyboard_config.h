#ifndef KEYBOARD_CONFIG_H
#define KEYBOARD_CONFIG_H 

#include <stdint.h>
#define N_ROWS 3
#define N_COLS 3
#define MAX_CONCURRENT_KEYS 6

static const uint8_t ROW_PINS[N_ROWS] = {0, 0, 0};
static const uint8_t COL_PINS[N_COLS] = {0, 0, 0};

static const uint32_t US_PER_ROW = 800;

void configure_keyboard();

#endif // !KEYBOARD_CONFIG_H
