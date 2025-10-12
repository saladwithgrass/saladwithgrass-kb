#ifndef I2C_LED_H_
#define I2C_LED_H_

#include "../RP2040/RP2040.h"
#include <stdint.h>

#define LCD_ADDRESS 0x27
#define LCD_COLS    16
#define LCD_ROWS    2

#define LCD_MODE_DATA 1
#define LCD_MODE_CMD  0

#define LCD_ENABLE_BIT 0x04

#define LCD_FLAG_BACKLIGHT 0x08

#define LCD_ENTRYMODESET    0x04
#define LCD_ENTRYLEFT       0x02

#define LCD_FUNCTIONSET     0x20
#define LCD_2LINE           0x08

#define LCD_DISPLAYCONTROL  0x08
#define LCD_DISPLAYON       0x04
#define LCD_CLEARDISPLAY    0x01


extern uint8_t LCD_STATE;

void lcd_send_byte(uint8_t byte, uint8_t is_data);
void lcd_send_half_byte(uint8_t half_byte);
void lcd_init();
void lcd_clear();
void lcd_char(char c);
void lcd_print(const char* str);
void lcd_set_cursor(uint8_t row, uint8_t col);
int lcd_i2c_run_test();

#endif // !I2C_LED_H_
