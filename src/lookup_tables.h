#ifndef LOOKUP_TABLES_H
#define LOOKUP_TABLES_H

#include "enemy.h"
#include "powerup.h"

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

extern level_object level_1_1_lookup[];
extern const size_t level_1_1_lookup_size;

#endif
