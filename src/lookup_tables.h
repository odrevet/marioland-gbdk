#ifndef LOOKUP_TABLES_H
#define LOOKUP_TABLES_H

#include <stdint.h>

typedef enum {
  OBJECT_TYPE_ENEMY,
  OBJECT_TYPE_POWERUP,
  OBJECT_TYPE_PLATFORM_MOVING,
  OBJECT_TYPE_PLATFORM_FALLING,
  OBJECT_TYPE_PIPE
} object_type;

typedef struct {
  uint8_t type;
} enemy_params;

typedef struct {
  uint8_t range;
  uint8_t platform_direction;
  uint8_t width;
} platform_moving_params;

typedef struct {
  const unsigned char* destination;
  uint8_t bank;
  uint8_t direction;
} pipe_params;

typedef struct {
  uint16_t x;
  uint8_t y;
  object_type type;

  union {
    enemy_params enemy;
    platform_moving_params platform_moving;
    pipe_params pipe;
  } data;
} level_object;

#endif
