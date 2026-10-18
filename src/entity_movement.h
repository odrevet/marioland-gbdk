#ifndef ENTITY_MOVEMENT_H
#define ENTITY_MOVEMENT_H

#include <gbdk/platform.h>
#include <stdbool.h>
#include <stdint.h>

#include "global.h"

/**
 * Shared goomba-like movement helpers.
 *
 * Enemies (goomba, koopa, ...) and the mushroom powerup all move the same way:
 * walk horizontally, bounce on walls/cliffs and fall with gravity.
 *
 * The code lives in a bank (see #pragma bank in entity_movement.c) because
 * ROM bank 0 is limited.
 */

/**
 * true when a width x height block at (x, y) upscaled position has solid ground
 * under it.
 */
uint8_t entity_has_ground(uint16_t x, uint16_t y, uint8_t width,
                          uint8_t height) BANKED;

/**
 * true when there is solid ground in front of the entity for the given
 * horizontal velocity. Used to make entities turn around at cliffs.
 */
uint8_t entity_has_ground_ahead(uint16_t x, uint16_t y, int8_t vel_x,
                                uint8_t width, uint8_t height) BANKED;

/**
 * Apply horizontal velocity, bouncing off walls (and cliffs when check_cliffs
 * is set). Updates *x, *vel_x and *flip in place.
 */
void entity_apply_horizontal_movement(uint16_t *x, uint16_t y, int8_t *vel_x,
                                      bool *flip, uint8_t width, uint8_t height,
                                      uint8_t top_margin,
                                      uint8_t check_cliffs) BANKED;

/**
 * Apply gravity and vertical velocity, landing on solid ground and stopping
 * when hitting a ceiling. Updates *y and *vel_y in place.
 */
void entity_apply_vertical_movement(uint16_t x, uint16_t *y, int8_t *vel_y,
                                    uint8_t width, uint8_t height,
                                    uint8_t top_margin, int8_t gravity_divisor,
                                    uint8_t on_ground) BANKED;

#endif
