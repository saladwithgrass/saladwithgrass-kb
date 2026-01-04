#ifndef KEYMAPPER_H
#define KEYMAPPER_H
#include "keyboard_config.h"
#include "pin_polling.h"
#include "class/hid/hid.h"
#include <stdint.h>

static const uint8_t keymap[N_ROWS][N_COLS] = {
    {HID_KEY_6, HID_KEY_7, HID_KEY_8, HID_KEY_9, HID_KEY_0, HID_KEY_BACKSPACE},
    {HID_KEY_Y, HID_KEY_U, HID_KEY_I, HID_KEY_O, HID_KEY_P, HID_KEY_EQUAL},
    {HID_KEY_H, HID_KEY_J, HID_KEY_K, HID_KEY_L, HID_KEY_SEMICOLON, HID_KEY_APOSTROPHE},
    {HID_KEY_N, HID_KEY_M, HID_KEY_COMMA, HID_KEY_PERIOD, HID_KEY_BACKSLASH, HID_KEY_SHIFT_RIGHT}
};

uint8_t get_keycode(key_position pos);

#endif // !KEYMAPPER_H_
