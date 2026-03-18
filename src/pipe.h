#ifndef PIPE_H
#define PIPE_H

#include <stdbool.h>
#include <stdint.h>
#include "level_object.h"

extern bool pipe_active;
extern pipe_params active_pipe;
extern uint16_t active_pipe_world_x;
extern uint8_t  active_pipe_y;

void pipe_reset(void);
void pipe_new(uint16_t world_x, uint8_t y, pipe_params params);

#endif