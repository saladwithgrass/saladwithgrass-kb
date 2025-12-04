#include "bsp/board_api.h"
#include "keyboard_config.h"
#include "keymap.h"
#include "pin_polling.h"
#include "tusb.h"
#include "pico.h"
#include "usb_descriptors.h"
#include "keyboard.h"

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(void) {
    // Poll every 10ms
    const uint32_t interval_ms = 10;
    static uint32_t start_ms = 0;

    if ( board_millis() - start_ms < interval_ms) return; // not enough time
    start_ms += interval_ms;

    uint32_t const btn = board_button_read();

    // Remote wakeup
    if ( tud_suspended() && btn )
    {
        // Wake up host if we are in suspend mode
        // and REMOTE_WAKEUP feature is enabled by host
        tud_remote_wakeup();
    }else
    {
        // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
        send_hid_report(REPORT_ID_KEYBOARD, btn);
    }
}

static void send_hid_report(uint8_t report_id, key_position presses[MAX_CONCURRENT_KEYS]) {
    // skip if hid is not ready yet
    if ( !tud_hid_ready() ) return;

    switch(report_id) {
        case REPORT_ID_KEYBOARD: {
                
                // use to avoid send multiple consecutive zero report for keyboard
                static bool has_keyboard_key = false;
                if (presses != NULL) {
                    uint8_t keycode[6] = { 0 };
                    for (int i = 0; i < MAX_CONCURRENT_KEYS; ++i) {
                        keycode[i] = get_keycode(presses[i]);
                        has_keyboard_key = has_keyboard_key || (keycode[i] != 0);
                    }
                    // XXX may be a problem with modifier here
                    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
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

    if (next_report_id < REPORT_ID_COUNT)
    {
        send_hid_report(next_report_id, NULL);
    }
}
