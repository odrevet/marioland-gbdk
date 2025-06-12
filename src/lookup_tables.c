#include "lookup_tables.h"
#include "enemy.h"
#include "platforms.h"
#include "powerup.h"
#include "stddef.h"

// 1_1
level_object level_1_1_lookup[] = {
    /*{.x = 22,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},*/
    /*{.x = 65,
     .y = 14,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},*/
    {.x = 26,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction =
                                  DIRECTION_VERTICAL}}, // TEST PLATFORM
    {.x = 280,
     .y = 10,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_VERTICAL}},
    {.x = 284,
     .y = 10,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_HORIZONTAL}}};

size_t level_1_1_lookup_size =
    sizeof(level_1_1_lookup) / sizeof(level_1_1_lookup[0]);

level_block_object const level_1_1_blocks_lookup[] = {
    {22, 9, POWERUP_MUSHROOM}};

const size_t level_1_1_blocks_lookup_size =
    sizeof(level_1_1_blocks_lookup) / sizeof(level_block_object);

// 1_2
level_object level_1_2_lookup[] = {
    {.x = 106,
     .y = 5,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 112,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 188,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 193,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 198,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 226,
     .y = 10,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_HORIZONTAL}},
    {.x = 263,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}}};

size_t level_1_2_lookup_size =
    sizeof(level_1_2_lookup) / sizeof(level_1_2_lookup[0]);

// 1_3
level_object level_1_3_lookup[] = {{.x = 0, .y = 0}};

size_t level_1_3_lookup_size =
    sizeof(level_1_3_lookup) / sizeof(level_1_3_lookup[0]);

// 2_1
level_object level_2_1_lookup[] = {{.x = 0, .y = 0}};

size_t level_2_1_lookup_size =
    sizeof(level_2_1_lookup) / sizeof(level_2_1_lookup[0]);

// 2_2
level_object level_2_2_lookup[] = {{.x = 0, .y = 0}};

size_t level_2_2_lookup_size =
    sizeof(level_2_2_lookup) / sizeof(level_2_2_lookup[0]);

// 2_3
level_object level_2_3_lookup[] = {{.x = 0, .y = 0}};

size_t level_2_3_lookup_size =
    sizeof(level_2_3_lookup) / sizeof(level_2_3_lookup[0]);

// 3_1
level_object level_3_1_lookup[] = {{.x = 0, .y = 0}};

size_t level_3_1_lookup_size =
    sizeof(level_3_1_lookup) / sizeof(level_3_1_lookup[0]);

// 3_2
level_object level_3_2_lookup[] = {{.x = 0, .y = 0}};

size_t level_3_2_lookup_size =
    sizeof(level_3_2_lookup) / sizeof(level_3_2_lookup[0]);

// 3_3
level_object level_3_3_lookup[] = {{.x = 0, .y = 0}};

size_t level_3_3_lookup_size =
    sizeof(level_3_3_lookup) / sizeof(level_3_3_lookup[0]);

// 4_1
level_object level_4_1_lookup[] = {{.x = 0, .y = 0}};

size_t level_4_1_lookup_size =
    sizeof(level_4_1_lookup) / sizeof(level_4_1_lookup[0]);

// 4_2
level_object level_4_2_lookup[] = {{.x = 0, .y = 0}};

size_t level_4_2_lookup_size =
    sizeof(level_4_2_lookup) / sizeof(level_4_2_lookup[0]);

// 4_3
level_object level_4_3_lookup[] = {{.x = 0, .y = 0}};

size_t level_4_3_lookup_size =
    sizeof(level_4_3_lookup) / sizeof(level_4_3_lookup[0]);
