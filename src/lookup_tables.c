#include "lookup_tables.h"

level_object level_1_1_lookup[] = {
    {3, 3, OBJECT_TYPE_ENEMY, ENEMY_GOOMBA},
    {6, 3, OBJECT_TYPE_POWERUP, POWERUP_MUSHROOM},
    {24, 6, OBJECT_TYPE_POWERUP, POWERUP_MUSHROOM}
};

const size_t level_1_1_lookup_size = sizeof(level_1_1_lookup) / sizeof(level_object);