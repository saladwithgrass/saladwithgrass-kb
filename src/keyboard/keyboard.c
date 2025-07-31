#include "../RP2040/RP2040.h"
// #include "../debug_matrix/debug_matrix.h"
#include "keyboard_config.h"
#include <stdint.h>

int notmain ( void ) {
    unsigned int ra;

    clock_init();
    init_IOBANK0();

    uint32_t output_pins_bytes = 0;
    uint32_t input_pins_bytes = 0;

    // configure_pins_debug_matrix();
    init_gpio_sio(1<<25, 0);
    // PUT32(SIO_GPIO_OUT_SET, (1<<25));
    // display_number(0b10110011);
    // return 0;

    // load configuration
    for (ra = 0; ra < N_OUTPUT_PINS; ++ra)
        output_pins_bytes = output_pins_bytes | (1 << OUTPUT_PINS[ra]);

    for (ra = 0; ra < N_INPUT_PINS; ++ra)
        input_pins_bytes = input_pins_bytes | (1 << INPUT_PINS[ra]);

    init_gpio_sio(output_pins_bytes, input_pins_bytes);

    // enable output for this pin
    PUT32(SIO_GPIO_OUT_SET, (1<<OUTPUT_PINS[0]));
    for (ra = 0; ra < 1000; ra++) {
        if (gpio_get(INPUT_PINS[0])){
            PUT32(SIO_GPIO_OUT_SET, 1<<DEBUG_PIN);
        } else {
            PUT32(SIO_GPIO_OUT_CLR, 1<<DEBUG_PIN);
        }
        delay(10);
    }


    return(0);
}

//-------------------------------------------------------------------------
//
// Copyright (c) 2021 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------
