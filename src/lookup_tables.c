#include "lookup_tables.h"
#include "enemy.h"
#include "platforms.h"
#include "powerup.h"

const level_object level_1_1_lookup[] = {
    {.x = 22,
     .y = 17,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    /*{.x = 65,
     .y = 14,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},*/
    {.x = 22,
     .y = 14,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},  // TEST PLATFORM
    {.x = 282,
     .y = 4,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_VERTICAL}},
    {.x = 284,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6, .platform_direction = DIRECTION_HORIZONTAL}}};

// Size of the lookup table
const size_t level_1_1_lookup_size =
    sizeof(level_1_1_lookup) / sizeof(level_1_1_lookup[0]);

level_block_object const level_1_1_blocks_lookup[] = {{22, 9, POWERUP_MUSHROOM}};

const size_t level_1_1_blocks_lookup_size =
    sizeof(level_1_1_blocks_lookup) / sizeof(level_block_object);
