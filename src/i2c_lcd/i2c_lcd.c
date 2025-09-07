#include "i2c_lcd.h"
#include "../RP2040/RP2040.h"
#include <stdint.h>

Error lcd_state_update() {
    Error write_result = write_byte_i2c(LCD_ADDRESS, LCD_STATE);
    if (write_result != ERROR_OK) {
        return write_result;
    }
    delay(100); 
    return ERROR_OK;
}

void lcd_pulse_e() {
    LCD_STATE |= (1 << 6); // E=1
    lcd_state_update();
    delay(1);           // tPW ≥ 230ns
    LCD_STATE &= ~(1 << 6); // E=0
    lcd_state_update();
    delay(1);
}

void lcd_send_half_byte(uint8_t half_byte) {
    LCD_STATE = (LCD_STATE & 0xF0) | (half_byte & 0x0F);
    lcd_state_update();
    lcd_pulse_e();
}

void lcd_send_byte(uint8_t byte, uint8_t is_data) {
    if (is_data) LCD_STATE |= (1<<4);
    else         LCD_STATE &= ~(1<<4);

    lcd_send_half_byte(byte>>4);
    lcd_send_half_byte(byte & 0x0F);
    delay(50);
}

// Initialize LCD (4-bit mode)
void lcd_init() {
    delay(15000); // >15ms after power-on
    
    // 1. Initialize sequence (must use 8-bit mode first)
    lcd_send_half_byte(0x03); delay(4100); // >4.1ms
    lcd_send_half_byte(0x03); delay(100);  // >100µs
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
    delay(2000); // Clear takes 1.52ms
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
