#ifndef PIPE_H
#define PIPE_H

#include <gbdk/platform.h>
#include <stdbool.h>
#include <stdint.h>
#include "level_object.h"

extern bool pipe_active;
extern pipe_params active_pipe;
extern uint8_t active_pipe_tile_x;
extern uint8_t active_pipe_tile_y;
extern uint8_t active_pipe_direction;

typedef enum {
  PIPE_DIRECTION_VERTICAL,
  PIPE_DIRECTION_HORIZONTAL,
} pipe_direction_t;

void pipe_new(uint8_t tile_x, uint8_t tile_y, uint8_t direction, pipe_params *params);
void pipe_clear(void);

#endif