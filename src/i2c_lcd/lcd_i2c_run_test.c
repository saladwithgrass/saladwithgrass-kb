#include "../RP2040/RP2040.h"
#include "i2c_lcd.h"
#include "../debug_matrix/debug_matrix.h"
#include <stdint.h>

const uint32_t sda_pin = 4;
const uint32_t scl_pin = 1;

int lcd_i2c_run_test() {
    // initialize all that has to be initialized
    clock_init();
    init_IOBANK0();

    configure_I2C0();
    // configure pin pads for I2C0
    configure_pads_I2C0(sda_pin, scl_pin);
    // configure pins for I2C0
    configure_pins_I2C0(sda_pin, scl_pin);

    set_I2C0_TAR(0x27);

    // while (1) {
    //     PUT32(I2C0_DATA_CMD, 'a');
    // }

    scan_addresses(sda_pin, scl_pin);
    init_gpio_sio(1<<25, 0);

    // test number display
    PUT32(SIO_GPIO_OUT_SET, (1<<25));
    display_number(255);
    delay(1000);

    display_number(1);
    delay(500);

    display_number(2);
    delay(500);

    // turn backlight off
    LCD_STATE &= ~(1<<7);
    lcd_state_update();
    display_number(3);
    delay(500);

    // turn backlight on
    LCD_STATE |= (1<<7);
    delay(100);

    lcd_init();
    lcd_print("bare metal rpi!");
    lcd_set_cursor(1, 0);
    lcd_print("no sdk");
    return 0;
}
