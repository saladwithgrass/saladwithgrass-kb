#ifndef KEYMAPPER_H
#define KEYMAPPER_H
#include "keyboard_config.h"
#include "pin_polling.h"
#include "class/hid/hid.h"
#include <stdint.h>

static const uint8_t keymap[N_ROWS][N_COLS] = {
    {HID_KEY_Y, HID_KEY_U, HID_KEY_I},
    {HID_KEY_H, HID_KEY_J, HID_KEY_K},
    {HID_KEY_N, HID_KEY_M, HID_KEY_COMMA}
};

uint8_t get_keycode(key_position pos);

#endif // !KEYMAPPER_H_
