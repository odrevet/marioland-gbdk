#include "lookup_tables.h"
#include "powerup.h"

level_object level_1_1_lookup[] = {
    {15, 17, OBJECT_TYPE_ENEMY, ENEMY_GOOMBO}
};

const size_t level_1_1_lookup_size = sizeof(level_1_1_lookup) / sizeof(level_object);


level_block_object level_1_1_blocks_lookup[] = {
    {22, 9, POWERUP_MUSHROOM}
};

const size_t level_1_1_blocks_lookup_size = sizeof(level_1_1_blocks_lookup) / sizeof(level_block_object);