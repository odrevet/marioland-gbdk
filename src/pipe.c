#include "pipe.h"

bool pipe_active = FALSE;
pipe_params active_pipe;
uint8_t active_pipe_tile_x;
uint8_t active_pipe_tile_y;

void pipe_new(uint8_t tile_x, uint8_t tile_y, pipe_params *params) {
    active_pipe_tile_x = tile_x;
    active_pipe_tile_y = tile_y;
    active_pipe = *params;
    pipe_active = TRUE;
}

void pipe_clear(void) {
    pipe_active = FALSE;
}