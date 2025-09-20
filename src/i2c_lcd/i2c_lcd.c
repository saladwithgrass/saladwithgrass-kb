#include "i2c_lcd.h"
#include "../RP2040/RP2040.h"
#include <stdint.h>

uint8_t LCD_STATE = 0x08;

void lcd_toggle_enable(uint8_t val) {
    // Toggle enable pin on LCD display
    // We cannot do this too quickly or things don't work
#define DELAY_US 600
    sleep_us(DELAY_US);
    i2c_write_byte(val | LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
    i2c_write_byte(val & ~LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
}

void lcd_send_byte(uint8_t byte, uint8_t is_data) {
    uint8_t high = is_data | (byte & 0xF0) | LCD_FLAG_BACKLIGHT;
    uint8_t low = is_data | ((byte << 4) & 0xF0) | LCD_FLAG_BACKLIGHT;

    write_byte_i2c(LCD_ADDRESS, high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

// Initialize LCD (4-bit mode)
void lcd_init() {
    delay_ms(15000); // >15ms after power-on
    
    // 1. Initialize sequence (must use 8-bit mode first)
    lcd_send_half_byte(0x03); delay_ms(4100); // >4.1ms
    lcd_send_half_byte(0x03); delay_ms(100);  // >100µs
    lcd_send_half_byte(0x03); 
    lcd_send_half_byte(0x02); // Switch to 4-bit mode
    
    // 2. Function set (4-bit, 2 lines, 5x8 font)
    lcd_send_byte(0x28, 0); // 0010 1000
    
    // 3. Display on/off control (Display on, cursor off, blink off)
    lcd_send_byte(0x0C, 0); // 0000 1100
    
    // 4. Entry mode set (increment, no shift)
    lcd_send_byte(0x06, 0); // 0000 0110
    
    // 5. Clear display
    lcd_send_byte(0x01, 0); // 0000 0001
    delay_ms(2000); // Clear takes 1.52ms
}

void lcd_print(const char* str) {
    while (*str) {
        lcd_send_byte(*(str++), 1); // 1 = data mode
    }
}

// Set cursor position (row=0/1, col=0-15)
void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t addr = col;
    if (row == 1) addr += 0x40; // Second line offset
    lcd_send_byte(0x80 | addr, 0); // Set DDRAM address

}
