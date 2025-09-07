#include "gpio.h"

#include "../resets.h"
#include <stddef.h>
#include <stdint.h>

void init_IOBANK0(void) {

    // unreset pins
    PUT32(RESETS_RESET_CLR, 1<<5); // IO_BANK0

    // wait for reset to clear
    while (1) {
        if ( (GET32(RESETS_RESET_DONE_RW) & (1<<5)) != 0)
            break;
    }

    // unreset pin pads
    PUT32(RESETS_RESET_CLR, (1<<8)); //PADS_BANK0

    // wait for pads to clear
    while (1) {
        if ( (GET32(RESETS_RESET_DONE_RW) & (1<<8)) != 0 ) break;
    }
}

void init_gpio_sio( uint32_t output_pins, uint32_t input_pins ) {

    uint32_t all_pins = output_pins | input_pins;
    // disable output for target pins
    PUT32(SIO_GPIO_OE_CLR, all_pins);
    // set output to zero for all target pins
    PUT32(SIO_GPIO_OUT_CLR, all_pins);

    for (int offset = 0; offset < NUM_PINS; ++offset) {
            PUT32(IO_BANK0_GPIO_CTRL_RW(offset), FUNCTION_SIO * (1 & (all_pins >> offset)));
    }
    // enable output for output pins
    PUT32(SIO_GPIO_OE_SET, output_pins);

}

uint8_t gpio_get(uint32_t gpio_n) {
    return ( GET32(SIO_GPIO_IN) & (1<<gpio_n));
}
