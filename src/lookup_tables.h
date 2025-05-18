#ifndef LOOKUP_TABLES_H
#define LOOKUP_TABLES_H

#include <stdbool.h>

#include "enemy.h"
#include "powerup.h"

typedef enum {
  OBJECT_TYPE_ENEMY,
  OBJECT_TYPE_POWERUP,
  OBJECT_TYPE_PLATFORM_MOVING,
  OBJECT_TYPE_PLATFORM_FALLING
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
  uint16_t x;
  uint8_t y;
  object_type type;

  union {
    enemy_params enemy;
    platform_moving_params platform_moving;
  } data;
} level_object;

typedef struct level_block_object {
  uint16_t x;
  uint8_t y;
  uint8_t id;
} level_block_object;

extern const level_object level_1_1_lookup[];
extern const size_t level_1_1_lookup_size;

extern const level_block_object level_1_1_blocks_lookup[];
extern const size_t level_1_1_blocks_lookup_size;

#endif
