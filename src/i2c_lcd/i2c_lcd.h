#ifndef I2C_LED_H_
#define I2C_LED_H_

#include "../RP2040/RP2040.h"
#include <stdint.h>

#define LCD_ADDRESS 0x27
#define LCD_COLS    16
#define LCD_ROWS    2

#define LCD_MODE_DATA 1
#define LCD_MODE_CMD  0

#define LCD_FLAG_BACKLIGHT 0x08

extern uint8_t LCD_STATE;

void lcd_send_byte(uint8_t byte, uint8_t is_data);
void lcd_send_half_byte(uint8_t half_byte);
void lcd_init();
void lcd_print(const char* str);
void lcd_set_cursor(uint8_t row, uint8_t col);
int lcd_i2c_run_test();

#endif // !I2C_LED_H_
