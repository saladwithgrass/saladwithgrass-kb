#include "keyboard.h"

#include "bsp/board_api.h"
#include "class/hid/hid.h"
#include "keyboard_config.h"
#include "keymap.h"
#include "pin_polling.h"
#include "tusb.h"
#include "pico.h"
#include "usb_descriptors.h"
#include <stdbool.h>
#include <stdint.h>

bool poll_keyboard(uint8_t keycodes[MAX_CONCURRENT_KEYS]) {
    key_position positions[MAX_CONCURRENT_KEYS];
    poll_and_get_presses(positions);
    bool return_val = false;
    for (int i = 0; i < MAX_CONCURRENT_KEYS; ++i) {
        keycodes[i] = get_keycode(positions[i]);
        // return_val = return_val || (keycodes[i] != 0);
        if (keycodes[i] == 0)
            return_val = true;
    }
    // board_led_write(return_val);
    return return_val;
}

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(void) {
    // Poll every 10ms
    const uint32_t interval_ms = 10;
    static uint32_t start_ms = 0;

    if ( board_millis() - start_ms < interval_ms) return; // not enough time
    start_ms += interval_ms;

    uint8_t keycodes[MAX_CONCURRENT_KEYS];
    bool any_press = poll_keyboard(keycodes);

    // Remote wakeup
    if ( tud_suspended() && any_press ) {
        // Wake up host if we are in suspend mode
        // and REMOTE_WAKEUP feature is enabled by host
        tud_remote_wakeup();
    } else {
        // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
        if (any_press) {
            send_hid_report(REPORT_ID_KEYBOARD, keycodes);
        }
        else {
            send_hid_report(REPORT_ID_KEYBOARD, NULL);
        }
    }
}


void send_hid_report(
        uint8_t report_id, 
        uint8_t keycodes[MAX_CONCURRENT_KEYS]
) {
    // skip if hid is not ready yet
    if ( !tud_hid_ready() ) return;

    switch(report_id) {
        case REPORT_ID_KEYBOARD: {
                
                // use to avoid send multiple consecutive zero report for keyboard
                static bool has_keyboard_key = false;

                if (keycodes != NULL) {
                    // XXX may be a problem with modifier here
                    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycodes);
                    has_keyboard_key = true;
                } else {
                   // send empty key report if previously has key pressed
                   if (has_keyboard_key) 
                       tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
                   has_keyboard_key = false;
               }
            }
            break;

/*
        case REPORT_ID_CONSUMER_CONTROL:
                                 {
                                     // use to avoid send multiple consecutive zero report
                                     static bool has_consumer_key = false;

                                     if ( btn )
                                     {
                                         // volume down
                                         uint16_t volume_down = HID_USAGE_CONSUMER_VOLUME_DECREMENT;
                                         tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &volume_down, 2);
                                         has_consumer_key = true;
                                     }else
                                     {
                                         // send empty key report (release key) if previously has key pressed
                                         uint16_t empty_key = 0;
                                         if (has_consumer_key) tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &empty_key, 2);
                                         has_consumer_key = false;
                                     }
                                 }
                                 break;
*/

        default: break;
    }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len)
{
    (void) instance;
    (void) len;

    uint8_t next_report_id = report[0] + 1u;
    static uint8_t keycodes[MAX_CONCURRENT_KEYS];
    bool any_press = poll_keyboard(keycodes);
    if (next_report_id < REPORT_ID_COUNT) {
        send_hid_report(next_report_id, any_press ? keycodes : NULL); // ooooo evil
    }
}

