#ifndef PLATFORMS_H
#define PLATFORMS_H

#include <gb/gb.h>
#include <gbdk/metasprites.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    PLATEFORM_TYPE_MOVING,
    PLATEFORM_TYPE_FALLING
} PLATEFORM_TYPE;

typedef enum {
    DIRECTION_HORIZONTAL,
    DIRECTION_VERTICAL
} PLATEFORM_DIRECTION;

typedef struct {
    uint16_t x;
    uint16_t y;
    PLATEFORM_TYPE type;
    uint8_t size;
    PLATEFORM_DIRECTION direction;
    uint8_t range;
} platform;

#endif 
