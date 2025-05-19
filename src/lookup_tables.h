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

// 1_1
extern level_object level_1_1_lookup[];
extern size_t level_1_1_lookup_size;

extern const level_block_object level_1_1_blocks_lookup[];
extern const size_t level_1_1_blocks_lookup_size;

// 1_2
extern level_object level_1_2_lookup[];
extern size_t level_1_2_lookup_size;

// 1_3
extern level_object level_1_3_lookup[];
extern size_t level_1_3_lookup_size;

// 2_1
extern level_object level_2_1_lookup[];
extern size_t level_2_1_lookup_size;

// 2_2
extern level_object level_2_2_lookup[];
extern size_t level_2_2_lookup_size;

// 2_3
extern level_object level_2_3_lookup[];
extern size_t level_2_3_lookup_size;

// 3_1
extern level_object level_3_1_lookup[];
extern size_t level_3_1_lookup_size;

// 3_2
extern level_object level_3_2_lookup[];
extern size_t level_3_2_lookup_size;

// 3_3
extern level_object level_3_3_lookup[];
extern size_t level_3_3_lookup_size;

// 4_1
extern level_object level_4_1_lookup[];
extern size_t level_4_1_lookup_size;

// 4_2
extern level_object level_4_2_lookup[];
extern size_t level_4_2_lookup_size;

// 4_3
extern level_object level_4_3_lookup[];
extern size_t level_4_3_lookup_size;

#endif
