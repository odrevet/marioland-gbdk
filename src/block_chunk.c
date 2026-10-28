#pragma bank 255

#include "block_chunk.h"
#include <gbdk/platform.h>
#include "global.h"
#include "level.h"
#include "commonSprites.h"

BANKREF(block_chunk)

block_chunk_t block_chunks[NB_BLOCK_CHUNK];
uint8_t block_chunk_index = 0;

// Frame index of the block chunk sprite in commonSprites.
#define BLOCK_CHUNK_FRAME 1
// How long (in frames) the chunks stay on screen before being hidden.
#define BLOCK_CHUNK_TTL 24
// Downward acceleration applied to every chunk so they eventually fall.
#define BLOCK_CHUNK_GRAVITY 2
// Number of chunks spawned when a block is broken.
#define BLOCK_CHUNK_PER_BREAK 4

// The four chunks are spread towards the four diagonals so they "splat" out
// of the block and then fall. Offsets are relative to the block's top-left.
static const int8_t chunk_offset_x[BLOCK_CHUNK_PER_BREAK] = {-2, 2, -2, 2};
static const int8_t chunk_offset_y[BLOCK_CHUNK_PER_BREAK] = {-2, -2, 2, 2};
static const int8_t chunk_vel_x[BLOCK_CHUNK_PER_BREAK] = {-1, 1, -1, 1};
static const int8_t chunk_vel_y[BLOCK_CHUNK_PER_BREAK] = {-3, -3, -1, -1};

void block_chunk_new(uint16_t world_x, uint16_t world_y) BANKED {
  for (uint8_t i = 0; i < BLOCK_CHUNK_PER_BREAK; i++) {
    block_chunk_t *chunk = &block_chunks[block_chunk_index];

    chunk->x = (int16_t)(world_x + chunk_offset_x[i]);
    chunk->y = (int16_t)(world_y + chunk_offset_y[i]);
    chunk->vx = chunk_vel_x[i];
    chunk->vy = chunk_vel_y[i];
    chunk->ttl = BLOCK_CHUNK_TTL;

    // Hide the slot until the next draw so a recycled slot never shows a
    // leftover sprite from a previous break.
    hide_sprite(BLOCK_CHUNK_HW_SPRITE_BASE + block_chunk_index);

    block_chunk_index++;
    if (block_chunk_index >= NB_BLOCK_CHUNK) {
      block_chunk_index = 0;
    }
  }
}

void block_chunk_update(void) BANKED {
  for (uint8_t i = 0; i < NB_BLOCK_CHUNK; i++) {
    block_chunk_t *chunk = &block_chunks[i];

    if (chunk->ttl == 0) {
      continue;
    }

    chunk->ttl--;
    if (chunk->ttl == 0) {
      hide_sprite(BLOCK_CHUNK_HW_SPRITE_BASE + i);
      continue;
    }

    chunk->vy = (int8_t)(chunk->vy + BLOCK_CHUNK_GRAVITY);
    chunk->x = (int16_t)(chunk->x + chunk->vx);
    chunk->y = (int16_t)(chunk->y + chunk->vy);
  }
}

uint8_t block_chunk_draw(uint8_t base_sprite) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(commonSprites));

  for (uint8_t i = 0; i < NB_BLOCK_CHUNK; i++) {
    block_chunk_t *chunk = &block_chunks[i];

    if (chunk->ttl == 0) {
      continue;
    }

    // Chunk positions are in world space so they scroll with the level.
    int16_t screen_x = (int16_t)(chunk->x - (int16_t)camera_x);
    int16_t screen_y = (int16_t)(chunk->y + MARGIN_TOP_PX);

    if (screen_x < -TILE_SIZE || screen_x > DEVICE_SCREEN_PX_WIDTH ||
        screen_y < -TILE_SIZE || screen_y > DEVICE_SCREEN_PX_HEIGHT) {
      hide_sprite(BLOCK_CHUNK_HW_SPRITE_BASE + i);
      continue;
    }

    // The metasprite origin is the sprite center, so offset by half a tile.
    move_metasprite_ex(commonSprites_metasprites[BLOCK_CHUNK_FRAME],
                       commonSprites_TILE_ORIGIN, 0,
                       BLOCK_CHUNK_HW_SPRITE_BASE + i,
                       (uint8_t)(screen_x + DEVICE_SPRITE_PX_OFFSET_X +
                                 (TILE_SIZE / 2)),
                       (uint8_t)(screen_y + DEVICE_SPRITE_PX_OFFSET_Y +
                                 (TILE_SIZE / 2)));
  }

  SWITCH_ROM(_saved_bank);

  return base_sprite;
}

void block_chunk_reset(void) BANKED {
  for (uint8_t i = 0; i < NB_BLOCK_CHUNK; i++) {
    block_chunks[i].ttl = 0;
  }
  block_chunk_index = 0;
}
