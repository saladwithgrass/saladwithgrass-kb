#ifndef PIN_POLLING_H
#define PIN_POLLING_H
#include <stddef.h>
#include <stdint.h>

typedef struct key_position_t_ {
    uint8_t row;
    uint8_t col;
} key_position ;


void poll_row(uint8_t row_id);
void poll_whole_kb();

void clear_presses();
void register_press(uint8_t row, uint8_t col);

void poll_and_get_presses(key_position* result);

#endif // !PIN_POLLING_H
