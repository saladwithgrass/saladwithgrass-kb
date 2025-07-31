#include "pads.h"
#include "../gpio/gpio.h"
#include "../general_defines.h"
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

Error pads_disable_input(uint8_t pad_num) {
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | GPIO_CLR, (1<<6));
    return ERROR_OK;
}

Error pads_enable_input(uint8_t pad_num) {
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | GPIO_SET, (1<<6));
    return ERROR_OK;
}

Error pads_set_drive(uint8_t pad_num, uint8_t value) {
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    if ((value != PADS_DRIVE_2MA) &&
        (value != PADS_DRIVE_4MA) &&
        (value != PADS_DRIVE_8MA) &&
        (value != PADS_DRIVE_12MA))
            return ERROR_BAD_ARGUMENTS;

    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | (value>>1) ? (GPIO_SET) : (GPIO_CLR), (1<<5));
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | (value & 1) ? (GPIO_SET) : (GPIO_CLR), (1<<4));
}

Error pads_enable_pullup(uint8_t pad_num) {
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | GPIO_SET, (1<<3));
    return ERROR_OK;
}

Error pads_diable_pullup(uint8_t pad_num) {
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | GPIO_CLR, (1<<3));
    return ERROR_OK;
}

Error pads_enable_pulldown(uint8_t pad_num) {
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | GPIO_SET, (1<<2));
    return ERROR_OK;
}

Error pads_diable_pulldown(uint8_t pad_num) {
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | GPIO_CLR, (1<<2));
    return ERROR_OK;
}

Error pads_enable_schmidt(uint8_t pad_num) {
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | GPIO_SET, (1<<1));
    return ERROR_OK;
}

Error pads_disable_schmidt(uint8_t pad_num) {
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | GPIO_CLR, (1<<1));
    return ERROR_OK;
}

Error pads_enable_fast_slewrate(uint8_t pad_num) {
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | GPIO_SET, (1));
    return ERROR_OK;
}

Error pads_disable_fast_slewrate(uint8_t pad_num) {
    if (!is_valid_pad(pad_num)) {
        return ERROR_BAD_ARGUMENTS;
    }
    PUT32(PADS_BANK0_GPIO_CTRL(pad_num) | GPIO_CLR, (1));
    return ERROR_OK;
}

