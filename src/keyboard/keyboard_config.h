#ifndef KEYBOARD_CONFIG_H
#define KEYBOARD_CONFIG_H

#include <stdint.h>

#define N_OUTPUT_PINS 5
#define COL0_PIN 10 // output
#define COL1_PIN 11 // output
#define COL2_PIN 12 // output
#define COL3_PIN 12 // output
#define DEBUG_PIN 25

const uint32_t OUTPUT_PINS[N_OUTPUT_PINS] = {
    COL0_PIN,
    COL1_PIN,
    COL2_PIN,
    COL3_PIN,
    DEBUG_PIN
};

#define N_INPUT_PINS 3
#define ROW0_PIN 0 // input
#define ROW1_PIN 1 // input
#define ROW2_PIN 2 // input

const uint32_t INPUT_PINS[N_INPUT_PINS] = {
    ROW0_PIN,
    ROW1_PIN,
    ROW2_PIN
};

#endif // !KEYBOARD_CONFIG_H
