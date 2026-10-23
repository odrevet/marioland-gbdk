#ifndef MISSILE_H
#define MISSILE_H

#include <gbdk/platform.h>
#include <stdbool.h>
#include <stdint.h>

// The submarine (world 2-3) can have three missiles in flight at the same time.
#define NB_MISSILE 3
// Fixed OAM slots for the missiles. They sit just below the block-chunk slots
// (32..39) so they never overlap the sequentially allocated gameplay sprites.
#define MISSILE_HW_SPRITE_BASE 29

BANKREF_EXTERN(missile)

typedef struct missile {
  int16_t x;   // world x of the missile top-left, in pixels
  int16_t y;   // world y of the missile top-left, in pixels
  uint8_t ttl; // remaining life in frames, 0 means inactive
} missile_t;

extern missile_t missiles[NB_MISSILE];

// Launch a missile from the given world position (top-left, in pixels).
// Does nothing when both missiles are already in flight.
void missile_fire(uint16_t world_x, uint16_t world_y) BANKED;
// Move the missiles and apply their collisions (blocks and enemies).
void missile_update(void) BANKED;
uint8_t missile_draw(uint8_t base_sprite) BANKED;
void missile_reset(void) BANKED;

#endif
