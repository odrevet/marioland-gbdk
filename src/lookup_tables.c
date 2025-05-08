#include "lookup_tables.h"
#include "powerup.h"

const level_object level_1_1_lookup[] = {
    {
        15,
        17,
        OBJECT_TYPE_ENEMY,
        {
            {
                15,
                17,
                0,
                0,
                -1,
                0,
                ENEMY_GOOMBO,
                0,
                0,
                1,
                true
            }
        }
    },
    {
        63,
        11,
        OBJECT_TYPE_ENEMY,
        {
            {
                63,
                11,
                0,
                0,
                1,
                0,
                ENEMY_KOOPA,
                0,
                0,
                1,
                false
            }
        }
    },

    // Moving platform
    {
        100,
        120,
        OBJECT_TYPE_PLATFORM_MOVING,
        {
            {
                100,
                120,
                0,
                0,
                1,
                0,
                3,
                6
            }
        }
    },
    {
        200,
        80,
        OBJECT_TYPE_PLATFORM_FALLING,
        {
            {
                200,
                80,
                0,
                0,
                false,
                30
            }
        }
    }
};

// Size of the lookup table
const size_t level_1_1_lookup_size =
    sizeof(level_1_1_lookup) / sizeof(level_1_1_lookup[0]);

level_block_object level_1_1_blocks_lookup[] = {{22, 9, POWERUP_MUSHROOM}};

const size_t level_1_1_blocks_lookup_size =
    sizeof(level_1_1_blocks_lookup) / sizeof(level_block_object);
