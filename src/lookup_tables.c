#include "lookup_tables.h"
#include "enemy.h"
#include "platforms.h"
#include "powerup.h"
#include "stddef.h"

// 1_1
level_object level_1_1_lookup[] = {
    {.x = 23,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 66,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 80,
     .y = 4,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 82,
     .y = 4,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 117,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 156,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 166,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_FLY}},
    {.x = 169,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 186,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 195,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 205,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 210,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 234,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_FLY}},
    {.x = 245,
     .y = 13,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_FLY}},
    {.x = 281,
     .y = 3,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.range = 6,
                              .platform_direction = DIRECTION_VERTICAL}},
    {.x = 283,
     .y = 1,
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
    {.x = 38,
     .y = 6,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 42,
     .y = 6,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 51,
     .y = 4,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 65,
     .y = 6,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 71,
     .y = 8,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 93,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 95,
     .y = 4,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 106,
     .y = 6,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 112,
     .y = 8,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 135,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 138,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 150,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 154,
     .y = 6,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
    {.x = 175,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 179,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
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
    {.x = 205,
     .y = 12,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 208,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_BUNBUN}},
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
level_object level_1_3_lookup[] = {
    {.x = 155,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GAO}},
    {.x = 187,
     .y = 10,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 251,
     .y = 12,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GAO}},
    {.x = 276,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GAO}},
    {.x = 292,
     .y = 11,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GAO}},
};

size_t level_1_3_lookup_size =
    sizeof(level_1_3_lookup) / sizeof(level_1_3_lookup[0]);

// 2_1
level_object level_2_1_lookup[] = {
    {.x = 28,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 32,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 53,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 57,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 63,
     .y = 10,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_HORIZONTAL}},
    {.x = 65,
     .y = 6,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_HORIZONTAL}},
    {.x = 104,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 111,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 122,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 131,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 129,
     .y = 6,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_KOOPA}},
    {.x = 129,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 134,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 143,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 147,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 156,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 161,
     .y = 5,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 163,
     .y = 5,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 174,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 176,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 178,
     .y = 2,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_GOOMBO}},
    {.x = 185,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 189,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 193,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 198,
     .y = 15,
     .type = OBJECT_TYPE_ENEMY,
     .data.enemy = {.type = ENEMY_HONEN}},
    {.x = 288,
     .y = 5,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
    {.x = 304,
     .y = 5,
     .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},
};

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
level_object level_3_2_lookup[] = {{.x = 7,
                                    .y = 3,
                                    .type = OBJECT_TYPE_ENEMY,
                                    .data.enemy = {.type = ENEMY_SUU}}};

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
