#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "pin_polling.h"
#include "keyboard_config.h"
#include <stdbool.h>
#include <stdint.h>

void hid_task(void);
void send_hid_report(
        uint8_t report_id, 
        uint8_t keycodes[MAX_CONCURRENT_KEYS]
);

/* 
 * Returns true if has any key pressed.
 * */
bool poll_keyboard(uint8_t keycodes[MAX_CONCURRENT_KEYS]);

#endif // !KEYBOARD_H
