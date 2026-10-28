#pragma bank 255

#include "powerup.h"
#include "entity_movement.h"
#include "level.h"

#define POWERUP_MUSHROOM_SPEED 4

// Constant fall speed of the mushroom when it has no ground (16 = 1 px/frame).
// Keep it a small value so it cannot sink into the ground before being detected.
#define POWERUP_MUSHROOM_FALL_SPEED 16

// Flower blink: alternates between these two frames of commonSprites.
#define POWERUP_FLOWER_FRAME_A 2
#define POWERUP_FLOWER_FRAME_B 7
// Number of frames each blink frame stays on screen (power of 2).
#define POWERUP_FLOWER_BLINK_FRAMES 8

// Spawn hop shared by the star and the mushroom: it first moves one tile up
// and one tile right, then one tile down and one tile right.
#define POWERUP_HOP_SPEED 8
#define POWERUP_HOP_RISE_HEIGHT (TILE_SIZE << 4)

// The star then falls straight down at a constant speed (no acceleration),
// without any background collision. 16 = 1 pixel per frame.
#define POWERUP_STAR_FALL_SPEED 16

#define MOVE_STATE_RISING 0
#define MOVE_STATE_DESCENDING 1
#define MOVE_STATE_FALLING 2
#define MOVE_STATE_WALKING 3

BANKREF(powerup)

bool powerup_active = FALSE;
powerup_t powerup;

static uint8_t flower_timer = 0;

void powerup_new(uint16_t x, uint16_t y, uint8_t type) BANKED {
  powerup.x = x;
  powerup.y = y;

  powerup.type = type;
  powerup.flip = FALSE;

  switch (powerup.type) {
  case POWERUP_MUSHROOM:
    powerup.current_frame = 0;
    powerup.vel_x = POWERUP_HOP_SPEED;
    powerup.vel_y = -POWERUP_HOP_SPEED;
    powerup.y_origin = y;
    powerup.move_state = MOVE_STATE_RISING;
    break;
  case POWERUP_STAR:
    powerup.current_frame = 5;
    powerup.vel_x = POWERUP_HOP_SPEED;
    powerup.vel_y = -POWERUP_HOP_SPEED;
    powerup.y_origin = y;
    powerup.move_state = MOVE_STATE_RISING;
    break;
  case POWERUP_FLOWER:
    // the flower is static: it stays where it spawned and blinks
    flower_timer = 0;
    powerup.current_frame = POWERUP_FLOWER_FRAME_A;
    powerup.vel_x = 0;
    powerup.vel_y = 0;
    break;
  }

  powerup_active = TRUE;
}

// Spawn hop, ignoring the background completely: rise diagonally up-right by
// one tile, then descend diagonally down-right by one tile.
// Returns TRUE once the hop is finished (back at the spawn height).
static bool powerup_hop_step(void) {
  int16_t rise_target = (int16_t)powerup.y_origin - POWERUP_HOP_RISE_HEIGHT;

  if (rise_target < 0) {
    rise_target = 0;
  }

  switch (powerup.move_state) {
  case MOVE_STATE_RISING:
    powerup.x += powerup.vel_x;

    if ((int16_t)powerup.y + powerup.vel_y <= rise_target) {
      powerup.y = (uint16_t)rise_target;
      powerup.vel_y = POWERUP_HOP_SPEED;
      powerup.move_state = MOVE_STATE_DESCENDING;
    } else {
      powerup.y += powerup.vel_y;
    }
    break;

  case MOVE_STATE_DESCENDING:
    powerup.x += powerup.vel_x;
    powerup.y += powerup.vel_y;

    if (powerup.y >= powerup.y_origin) {
      powerup.y = powerup.y_origin;
      return TRUE;
    }
    break;
  }

  return FALSE;
}

static void powerup_move_star(void) {
  if (powerup.move_state == MOVE_STATE_FALLING) {
    // straight down (90 degrees), constant speed
    powerup.y += powerup.vel_y;
    return;
  }

  if (powerup_hop_step()) {
    powerup.vel_x = 0;
    powerup.vel_y = POWERUP_STAR_FALL_SPEED;
    powerup.move_state = MOVE_STATE_FALLING;
  }
}

static void powerup_move_mushroom(void) {
  if (powerup.move_state != MOVE_STATE_WALKING) {
    if (powerup_hop_step()) {
      powerup.vel_x = POWERUP_MUSHROOM_SPEED;
      powerup.vel_y = 0;
      powerup.move_state = MOVE_STATE_WALKING;
    }
    return;
  }

  // the mushroom walks like a goomba: it moves horizontally and bounces off
  // walls. The horizontal code is shared with the enemies (see
  // entity_movement.c) because ROM bank 0 is limited.
  if (powerup.vel_x == 0) {
    powerup.vel_x = POWERUP_MUSHROOM_SPEED;
  }

  entity_apply_horizontal_movement(
      &powerup.x, powerup.y, &powerup.vel_x, &powerup.flip, TILE_SIZE,
      TILE_SIZE, 0, FALSE);

  // vertical: constant fall speed, no acceleration
  if (entity_has_ground(powerup.x, powerup.y, TILE_SIZE, TILE_SIZE)) {
    powerup.vel_y = 0;
  } else {
    powerup.vel_y = POWERUP_MUSHROOM_FALL_SPEED;
    powerup.y += powerup.vel_y;
  }
}

void powerup_update(void) BANKED {
  if (powerup.type == POWERUP_MUSHROOM) {
    powerup_move_mushroom();
  } else if (powerup.type == POWERUP_STAR) {
    powerup_move_star();
  } else if (powerup.type == POWERUP_FLOWER) {
    flower_timer++;
    powerup.current_frame =
        (flower_timer & POWERUP_FLOWER_BLINK_FRAMES) ? POWERUP_FLOWER_FRAME_B
                                                     : POWERUP_FLOWER_FRAME_A;
  }

  powerup.draw_x =
      ((powerup.x - camera_x_upscaled) >> 4) + DEVICE_SPRITE_PX_OFFSET_X + 4;
  powerup.draw_y = (powerup.y >> 4) + DEVICE_SPRITE_PX_OFFSET_Y + 2 * TILE_SIZE + 4;

  if (powerup.draw_x >= DEVICE_SCREEN_PX_WIDTH + 8 * TILE_SIZE) {
    powerup_active = FALSE;
  }

  if ((powerup.y >> 4) > DEVICE_SCREEN_PX_HEIGHT + 2 * TILE_SIZE) {
    powerup_active = FALSE;
  }
}

uint8_t powerup_draw(uint8_t base_sprite) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(commonSprites));

  const metasprite_t *commonSprites_metasprite =
      commonSprites_metasprites[powerup.current_frame];

#ifdef SEGA
  base_sprite += move_metasprite_ex(commonSprites_metasprite,
                                    commonSprites_TILE_ORIGIN, 0, base_sprite,
                                    powerup.draw_x, powerup.draw_y);
#else
  if (powerup.flip) {
    base_sprite += move_metasprite_flipx(commonSprites_metasprite,
                                         commonSprites_TILE_ORIGIN, 0,
                                         base_sprite, powerup.draw_x,
                                         powerup.draw_y);
  } else {
    base_sprite += move_metasprite_ex(commonSprites_metasprite,
                                      commonSprites_TILE_ORIGIN, 0, base_sprite,
                                      powerup.draw_x, powerup.draw_y);
  }
#endif

  SWITCH_ROM(_saved_bank);

  return base_sprite;
}