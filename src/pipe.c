#include "pipe.h"

bool pipe_active = FALSE;
pipe_params active_pipe;
uint16_t active_pipe_world_x;
uint8_t  active_pipe_y;

void pipe_reset(void) {
    pipe_active = FALSE;
}

void pipe_new(uint16_t world_x, uint8_t y, pipe_params params) {
    pipe_active        = TRUE;
    active_pipe_world_x = world_x;
    active_pipe_y       = y;
    active_pipe         = params;
}