#pragma bank 255
#include "lookup_table_1_2.h"
BANKREF(level_1_2_lookup)


static const level_object level_1_2_page_00_lookup[] = {{0}};


static const level_object level_1_2_page_01_lookup[] = {
    {.x = 18, .y = 6, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},   
};


static const level_object level_1_2_page_02_lookup[] = {
    {.x = 2,  .y = 6, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BUNBUN}},        
    {.x = 11, .y = 4, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BUNBUN}},        
};


static const level_object level_1_2_page_03_lookup[] = {
    {.x = 5,  .y = 6, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},         
    {.x = 11, .y = 8, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},         
};


static const level_object level_1_2_page_04_lookup[] = {
    {.x = 13, .y = 2, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_KOOPA}},         
    {.x = 15, .y = 4, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},        
};


static const level_object level_1_2_page_05_lookup[] = {
    {.x = 6,  .y = 6, .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},                       
    {.x = 12, .y = 8, .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},                       
};


static const level_object level_1_2_page_06_lookup[] = {
    {.x = 15, .y = 2, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BUNBUN}},        
    {.x = 18, .y = 2, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BUNBUN}},        
};


static const level_object level_1_2_page_07_lookup[] = {
    {.x = 10, .y = 2, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BUNBUN}},        
    {.x = 14, .y = 6, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_BUNBUN}},        
};


static const level_object level_1_2_page_08_lookup[] = {
    {.x = 15, .y = 2, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},        
    {.x = 19, .y = 2, .type = OBJECT_TYPE_ENEMY, .data.enemy = {.type = ENEMY_GOOMBO}},        
};


static const level_object level_1_2_page_09_lookup[] = {
    {.x = 8,  .y = 8, .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},                       
    {.x = 13, .y = 8, .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},                       
    {.x = 18, .y = 8, .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},                       
};


static const level_object level_1_2_page_10_lookup[] = {
    {.x = 5,  .y = 12, .type = OBJECT_TYPE_ENEMY,   .data.enemy = {.type = ENEMY_KOOPA}},      
    {.x = 8,  .y = 2,  .type = OBJECT_TYPE_ENEMY,   .data.enemy = {.type = ENEMY_BUNBUN}},     
};


static const level_object level_1_2_page_11_lookup[] = {
    {.x = 6,  .y = 10, .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_HORIZONTAL}},                     
};


static const level_object level_1_2_page_12_lookup[] = {{0}};


static const level_object level_1_2_page_13_lookup[] = {
    {.x = 3,  .y = 8, .type = OBJECT_TYPE_PLATFORM_MOVING,
     .data.platform_moving = {.platform_direction = DIRECTION_VERTICAL}},                       
};

const page_lookup_t level_1_2_lookup[] = {
    {level_1_2_page_00_lookup, BANK(level_1_2_lookup), 0},
    {level_1_2_page_01_lookup, BANK(level_1_2_lookup), 1},
    {level_1_2_page_02_lookup, BANK(level_1_2_lookup), 2},
    {level_1_2_page_03_lookup, BANK(level_1_2_lookup), 2},
    {level_1_2_page_04_lookup, BANK(level_1_2_lookup), 2},
    {level_1_2_page_05_lookup, BANK(level_1_2_lookup), 2},
    {level_1_2_page_06_lookup, BANK(level_1_2_lookup), 2},
    {level_1_2_page_07_lookup, BANK(level_1_2_lookup), 2},
    {level_1_2_page_08_lookup, BANK(level_1_2_lookup), 2},
    {level_1_2_page_09_lookup, BANK(level_1_2_lookup), 3},
    {level_1_2_page_10_lookup, BANK(level_1_2_lookup), 2},
    {level_1_2_page_11_lookup, BANK(level_1_2_lookup), 1},
    {level_1_2_page_12_lookup, BANK(level_1_2_lookup), 0},
    {level_1_2_page_13_lookup, BANK(level_1_2_lookup), 1},
};