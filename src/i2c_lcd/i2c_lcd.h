#ifndef I2C_LED_H_
#define I2C_LED_H_

#include "../RP2040/RP2040.h"
#include <stdint.h>

#define LCD_ADDRESS 0x27
#define LCD_COLS    16
#define LCD_ROWS    2

uint8_t LCD_STATE = 0x08; // P7=Backlight (1=on), P5=RW=0 (write)

// kind of stop signal
void lcd_pulse_e();

// send current state
Error lcd_state_update();

void lcd_send_half_byte(uint8_t half_byte);
void lcd_send_byte(uint8_t byte, uint8_t is_data);
void lcd_init();
void lcd_print(const char* str);
void lcd_set_cursor(uint8_t row, uint8_t col);

#endif // !I2C_LED_H_
