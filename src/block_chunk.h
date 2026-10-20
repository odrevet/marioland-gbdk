#ifndef BLOCK_CHUNK_H
#define BLOCK_CHUNK_H

#include <gbdk/platform.h>
#include <stdint.h>

// Number of chunks that can be on screen at once (2 broken blocks).
#define NB_BLOCK_CHUNK 8
// Fixed OAM slots used by the chunks, kept at the top of the sprite table so
// they don't collide with the sequentially allocated gameplay sprites.
#define BLOCK_CHUNK_HW_SPRITE_BASE 32

BANKREF_EXTERN(block_chunk)

typedef struct block_chunk {
  int16_t x;   // world x of the chunk sprite top-left, in pixels
  int16_t y;   // world y of the chunk sprite top-left, in pixels
  int8_t vx;   // horizontal velocity, pixels per frame
  int8_t vy;   // vertical velocity, pixels per frame
  uint8_t ttl; // remaining life in frames, 0 means inactive
} block_chunk_t;

extern block_chunk_t block_chunks[NB_BLOCK_CHUNK];
extern uint8_t block_chunk_index;

// Spawn the four debris chunks of a broken block at the given world tile
// position (top-left of the tile, in pixels).
void block_chunk_new(uint16_t world_x, uint16_t world_y) BANKED;
void block_chunk_update(void) BANKED;
uint8_t block_chunk_draw(uint8_t base_sprite) BANKED;
void block_chunk_reset(void) BANKED;

#endif
