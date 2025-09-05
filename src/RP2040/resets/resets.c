#include "../general_defines.h"
#include <stdint.h>
#include "resets.h"

inline void reset_subsystem(uint8_t subsytem) {
    PUT32(RESETS_RESET_SET, (1<<subsytem));
}

inline void unreset_subsystem(uint8_t subsytem) {
    PUT32(RESETS_RESET_CLR, (1<<subsytem));
    // wait for rest to be done
    while ( is_reset_done(subsytem) == 0 ) {}
}

inline uint8_t is_reset_done(uint8_t subsytem){
    return (GET32(RESETS_RESET_DONE_RW)) & (1<<subsytem);
}
