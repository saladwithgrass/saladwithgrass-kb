#include "keymap.h"
#include "keyboard_config.h"

extern const uint8_t keymap[N_ROWS][N_COLS];

inline uint8_t get_keycode(key_position pos) {
    uint8_t pos_in_range = pos.col < N_COLS && pos.row < N_ROWS;
    if (!pos_in_range)
        return 0;
    return keymap[pos.row][pos.col];
}

