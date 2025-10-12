#include "i2c_lcd.h"
#include "../debug_matrix/debug_matrix.h"
#include "../RP2040/RP2040.h"
#include <stdint.h>

uint8_t LCD_STATE = 0x08;

void lcd_toggle_enable(uint8_t val) {
    // Toggle enable pin on LCD display
    // We cannot do this too quickly or things don't work
#define DELAY_US 600
    delay_us(DELAY_US);
    write_byte_i2c(LCD_ADDRESS, val | LCD_ENABLE_BIT);
    delay_us(DELAY_US);
    write_byte_i2c(LCD_ADDRESS, val & ~LCD_ENABLE_BIT);
    delay_us(DELAY_US);
}

void lcd_send_byte(uint8_t byte, uint8_t is_data) {
    uint8_t high = is_data | (byte & 0xF0) | LCD_FLAG_BACKLIGHT;
    uint8_t low = is_data | ((byte << 4) & 0xF0) | LCD_FLAG_BACKLIGHT;

    Error err = write_byte_i2c(LCD_ADDRESS, high);
    if (err != 0) {
        blink_and_display_error(err);
    }
    lcd_toggle_enable(high);
    err = write_byte_i2c(LCD_ADDRESS, low);
    if (err != 0) {
        blink_and_display_error(err);
    }
    lcd_toggle_enable(low);
}

void lcd_clear() {
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_MODE_CMD);
}

// Initialize LCD (4-bit mode)
void lcd_init() {
    delay_ms(15); // >15ms after power-on

    lcd_send_byte(0x03, LCD_MODE_CMD);
    lcd_send_byte(0x03, LCD_MODE_CMD);
    lcd_send_byte(0x03, LCD_MODE_CMD);
    lcd_send_byte(0x02, LCD_MODE_CMD);

    lcd_send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT,   LCD_MODE_CMD);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE,        LCD_MODE_CMD);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_MODE_CMD);
    lcd_clear();
}

void lcd_char(char c) {
    lcd_send_byte(c, LCD_MODE_DATA);
}

void lcd_print(const char* str) {
    while (*str) {
        lcd_char(*str); // 1 = data mode
        str++;
    }
}

// Set cursor position (row=0/1, col=0-15)
void lcd_set_cursor(uint8_t row, uint8_t col) {
    // uint8_t addr = col;
    // if (row == 1) addr += 0x40; // Second line offset
    // lcd_send_byte(0x80 | addr, 0); // Set DDRAM address
    int val = (row == 0) ? 0x80 + col : 0xC0 + col;
    lcd_send_byte(val, LCD_MODE_CMD);
}
