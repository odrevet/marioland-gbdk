#ifndef LOOKUP_TABLES_H
#define LOOKUP_TABLES_H

#include "enemy.h"
#include "platforms.h"
#include "powerup.h"

typedef enum {
    OBJECT_TYPE_ENEMY,
    OBJECT_TYPE_POWERUP,
    OBJECT_TYPE_PLATFORM_MOVING,
    OBJECT_TYPE_PLATFORM_FALLING
} object_type;

typedef struct {
    uint16_t x;
    uint8_t y;
    object_type type;

    union {
        enemy_t enemy;
        platform_moving_t platform_moving;
        platform_falling_t platform_falling;
    } data;
} level_object;

typedef struct level_block_object {
    uint16_t x;
    uint8_t y;
    uint8_t id;
} level_block_object;

extern level_object level_1_1_lookup[];
extern const size_t level_1_1_lookup_size;

extern level_block_object level_1_1_blocks_lookup[];
extern const size_t level_1_1_blocks_lookup_size;

#endif
