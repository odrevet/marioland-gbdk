#ifndef LOOKUP_TABLES_H
#define LOOKUP_TABLES_H

#include "enemy.h"
#include "powerup.h"
#include <cstdint>

typedef enum {
    OBJECT_TYPE_ENEMY,
    OBJECT_TYPE_POWERUP
} object_type;

typedef struct {
    uint16_t x;
    uint16_t y;
    object_type type;
    uint8_t id;
} level_object;

level_object level_1_1_lookup[] = {
    {3, 3, OBJECT_TYPE_ENEMY, ENEMY_GOOMBA},
    {6, 3, OBJECT_TYPE_POWERUP, POWERUP_MUSHROOM}
};

#endif
