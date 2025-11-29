#include "general_defines.h"
#include <stdint.h>

void write_masked(
        unsigned int reg, 
        unsigned int value, 
        unsigned int mask) {

    uint32_t current_value = GET32(reg);
    // make target bits zero
    current_value = current_value & (~mask);
    // set target bits
    current_value = current_value | (value & mask);
    PUT32(reg, current_value);
}
