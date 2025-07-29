#include "pads.h"
#include "gpio.h"
#include "general_defines.h"
#include <stdint.h>

uint8_t is_valid_pad(uint8_t pad_num) {
    return pad_num < NUM_PINS;
}

Error pads_disable_ouput(uint8_t pad_num) {
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | GPIO_SET, (1<<7) );
    return ERROR_OK;
}

Error pads_enable_ouput(uint8_t pad_num){
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | GPIO_CLR, (1<<7) );
    return ERROR_OK;

}

Error pads_disable_input(uint8_t pad_num);
Error pads_enable_input(uint8_t pad_num);

Error pads_set_drive(uint8_t pad_num, uint8_t value);

Error pads_enable_pullup(uint8_t pad_num);
Error pads_diable_pullup(uint8_t pad_num);

Error pads_enable_pulldown (uint8_t pad_num);
Error pads_disable_pulldown(uint8_t pad_num);

Error pads_disable_schmidt (uint8_t pad_num);
Error pads_enable_schmidt(uint8_t pad_num);

Error pads_enable_fast_slewrate(uint8_t pad_num);
Error pads_disable_fast_slewrate(uint8_t pad_num);
