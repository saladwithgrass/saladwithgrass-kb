#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "pin_polling.h"
#include "keyboard_config.h"
#include <stdint.h>

void hid_task(void);
static void send_hid_report(
        uint8_t report_id, 
        key_position presses[MAX_CONCURRENT_KEYS]);

#endif // !KEYBOARD_H
