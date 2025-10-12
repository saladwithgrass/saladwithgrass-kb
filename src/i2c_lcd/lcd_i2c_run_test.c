#include "../RP2040/RP2040.h"
#include "i2c_lcd.h"
#include "../debug_matrix/debug_matrix.h"
#include <stddef.h>
#include <stdint.h>

const uint32_t sda_pin = 4;
const uint32_t scl_pin = 1;

size_t strlen(const char * str) {
    size_t result = 0;
    while (*str) {
        str++;
        result++;
    }
    return result;
}

int lcd_i2c_run_test() {
    // initialize all that has to be initialized
    clock_init();
    init_IOBANK0();
    //display_number(1);

    //for (int i = 0; i < 5; ++i) {
    //    display_number(i);
    //    delay_ms(1000);
    //}
    display_number(1);
    delay_ms(100);
    configure_I2C0();
    display_number(3);
    delay_ms(100);
    // configure pin pads for I2C0
    configure_pads_I2C0(sda_pin, scl_pin);
    // configure pins for I2C0
    configure_pins_I2C0(sda_pin, scl_pin);

    display_number(6);
    delay_ms(100);
    lcd_init();
    char *message[] =
            {
                    "IT FUCKIN", "WORKS",
                    "A brand new", "microcontroller",
                    "Twin core M0", "Full C SDK",
                    "More power in", "your product",
                    "More beans", "than Heinz!"
            };

    char *works_message = "IT FN WORKS";
    size_t msg_len = strlen(works_message);
    display_number(254);
    delay_ms(1000);
    lcd_set_cursor(0, 0);
    display_number(255);
    delay_ms(1000);
    lcd_print(works_message);
    display_number(255);
    return 0;
    while (1) {
        for (size_t m = 0; m < (sizeof(message) / sizeof(message[0])); m += LCD_ROWS) {
            for (int line = 0; line < LCD_ROWS; line++) {
                display_number(2+4+8+16+32+64+128);
                delay_ms(1000);
                lcd_set_cursor(line, (LCD_COLS / 2) - strlen(message[m + line]) / 2);
                display_number(255);
                delay_ms(1000);
                lcd_print(message[m + line]);
            }
            display_number(255);
            delay_ms(2000);
            lcd_clear();
        }
    }

    // while (1) {
    //     PUT32(I2C0_DATA_CMD, 'a');
    // }

    // scan_addresses(sda_pin, scl_pin);
    // init_gpio_sio(1<<25, 0);

    // // test number display
    // PUT32(SIO_GPIO_OUT_SET, (1<<25));
    // display_number(255);
    // delay_ms(1000);

    // display_number(1);
    // delay_ms(500);

    // display_number(2);
    // delay_ms(500);

    // // turn backlight off
    // LCD_STATE &= ~(1<<7);
    // lcd_state_update();
    // display_number(3);
    // delay_ms(500);

    // // turn backlight on
    // LCD_STATE |= (1<<7);
    // delay_ms(100);

    // lcd_init();
    // lcd_print("bare metal rpi!");
    // lcd_set_cursor(1, 0);
    // lcd_print("no sdk");
    return 0;
}
