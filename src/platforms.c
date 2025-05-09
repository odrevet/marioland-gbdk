#include "platforms.h"

void platform_moving_new(uint16_t x, uint16_t y, plateform_direction_t direction, uint8_t range) {
    EMU_printf("Platform moving at %d %d; params %d %d\n", x, y, direction, range);
}

void platform_falling_new(uint16_t x, uint16_t y) {}
