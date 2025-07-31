#include "debug_matrix.h"
#include "../RP2040/gpio/gpio.h"

void display_number(uint8_t number) {
    init_gpio_sio(DBG_MATRIX_ALL_PINS, 0);
    PUT32(SIO_GPIO_OUT_CLR, DBG_MATRIX_ALL_PINS);
    PUT32(SIO_GPIO_OUT_SET, (1<<DBG_MATRIX_POWER_PIN));

    PUT32(SIO_GPIO_OUT_SET, (((number>>0) & 1) << DBG_MATRIX_PIN0));
    PUT32(SIO_GPIO_OUT_SET, (((number>>1) & 1) << DBG_MATRIX_PIN1));
    PUT32(SIO_GPIO_OUT_SET, (((number>>2) & 1) << DBG_MATRIX_PIN2));
    PUT32(SIO_GPIO_OUT_SET, (((number>>3) & 1) << DBG_MATRIX_PIN3));
    PUT32(SIO_GPIO_OUT_SET, (((number>>4) & 1) << DBG_MATRIX_PIN4));
    PUT32(SIO_GPIO_OUT_SET, (((number>>5) & 1) << DBG_MATRIX_PIN5));
    PUT32(SIO_GPIO_OUT_SET, (((number>>6) & 1) << DBG_MATRIX_PIN6));
    PUT32(SIO_GPIO_OUT_SET, (((number>>7) & 1) << DBG_MATRIX_PIN7));
}
    
void configure_pins_debug_matrix() {

}
