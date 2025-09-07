#ifndef DEBUG_MATRIX_H_
#define DEBUG_MATRIX_H_
#include <stdint.h>

#define N_BITS 8

#define DBG_MATRIX_PIN7 16
#define DBG_MATRIX_PIN6 17
#define DBG_MATRIX_PIN5 18
#define DBG_MATRIX_PIN4 19
#define DBG_MATRIX_PIN3 20
#define DBG_MATRIX_PIN2 21
#define DBG_MATRIX_PIN1 22
#define DBG_MATRIX_PIN0 26

#define DBG_MATRIX_POWER_PIN 23

#define DBG_MATRIX_ALL_PINS (\
        (1<<DBG_MATRIX_PIN7) | \
        (1<<DBG_MATRIX_PIN6) | \
        (1<<DBG_MATRIX_PIN5) | \
        (1<<DBG_MATRIX_PIN4) | \
        (1<<DBG_MATRIX_PIN3) | \
        (1<<DBG_MATRIX_PIN2) | \
        (1<<DBG_MATRIX_PIN1) | \
        (1<<DBG_MATRIX_PIN0) | \
        (1<<DBG_MATRIX_POWER_PIN))


void display_number(uint8_t number);
void configure_pins_debug_matrix();

#endif // !DEBUG_MATRIX_H_
