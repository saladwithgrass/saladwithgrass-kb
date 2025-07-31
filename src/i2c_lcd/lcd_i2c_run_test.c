#include "../RP2040/RP2040.h"
#include "i2c_lcd.h"
#include "../debug_matrix/debug_matrix.h"
#include <stdint.h>

const uint32_t sda_pin = 12;
const uint32_t scl_pin = 10;

int lcd_i2c_run_test() {
    clock_init();
    init_IOBANK0();

    init_gpio_sio(1<<25, 0);
    PUT32(SIO_GPIO_OUT_SET, (1<<25));
    display_number(255);
    delay(100);
    configure_pads_I2C0(sda_pin, scl_pin);
    display_number(1);
    delay(100);
    configure_pins_I2C0(sda_pin, scl_pin);
    return 0;
    // turn backlight off
    LCD_STATE &= ~(1<<7);
    delay(100);
    // turn backlight on
    LCD_STATE |= (1<<7);
    delay(100);

    lcd_init();
    lcd_print("bare metal rpi!");
    lcd_set_cursor(1, 0);
    lcd_print("no sdk");
    return 0;
}
