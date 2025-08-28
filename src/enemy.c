#include "enemy.h"
#include "global.h"
#include "level.h"
#include <stdint.h>

uint8_t enemy_count = 0;
enemy_t enemies[ENEMY_MAX];

#include <gbdk/emu_debug.h>

void enemy_new(uint16_t x, uint16_t y, uint8_t type) {
  EMU_printf("enemy new at %d %d\n", x, y);
  if (enemy_count < ENEMY_MAX) {
    uint8_t current_frame;
    int8_t vel_x = 0;
    switch (type) {
    case ENEMY_GOOMBO:
      current_frame = 0;
      vel_x = 0; // WIP
      y -= 8;
      break;
    case ENEMY_KOOPA:
      current_frame = 1;
      vel_x = 0; // WIP
      y -= 8;
      break;
    }
    enemy_t enemy = {.x = x << 4,
                     .y = y << 4,
                     .vel_x = vel_x,
                     .vel_y = 0,
                     .type = type,
                     .frame_counter = 0,
                     .current_frame = current_frame,
                     .flip = FALSE};
    enemies[enemy_count] = enemy;
    enemy_count++;
  }
}


#define ENEMY_WIDTH 8
#define ENEMY_HEIGHT 16
#define ENEMY_GOOMBA_SPEED 4
#define ENEMY_TOP_MARGIN 0
#define ENEMY_GRAVITY 32

void enemy_move_goomba(uint8_t index) {
  enemy_t *goomba = &enemies[index];

  // Set initial velocity if not moving
  if (goomba->vel_x == 0) {
    goomba->vel_x = -ENEMY_GOOMBA_SPEED; // Start moving left
  }

  // Calculate next position
  uint16_t next_x_upscaled = goomba->x + goomba->vel_x;
  uint16_t next_y_upscaled = goomba->y + goomba->vel_y;

  uint16_t next_x = next_x_upscaled >> 4;
  uint16_t next_y = next_y_upscaled >> 4;
  uint16_t current_x = goomba->x >> 4;
  uint16_t current_y = goomba->y >> 4;

  // Horizontal movement and collision detection
  if (goomba->vel_x > 0) {
    // Moving right - check right edge
    uint8_t tile_right_top = get_tile(next_x + ENEMY_WIDTH - 1 - camera_x,
                                      current_y + ENEMY_TOP_MARGIN);
    uint8_t tile_right_bottom = get_tile(next_x + ENEMY_WIDTH - 1 - camera_x,
                                         current_y + ENEMY_HEIGHT - 1);

    if (is_tile_solid(tile_right_top) || is_tile_solid(tile_right_bottom)) {
      // Hit wall, reverse direction
      goomba->vel_x = -ENEMY_GOOMBA_SPEED;
      goomba->flip = TRUE;
    } else {
      // Check for cliff (no ground ahead when moving right)
      uint8_t tile_ground_ahead =
          get_tile(next_x + ENEMY_WIDTH - camera_x, current_y + ENEMY_HEIGHT);
      if (!is_tile_solid(tile_ground_ahead)) {
        // No ground ahead, reverse direction
        goomba->vel_x = -ENEMY_GOOMBA_SPEED;
        goomba->flip = TRUE;
      } else {
        // Safe to move
        goomba->x = next_x_upscaled;
      }
    }
  } else if (goomba->vel_x < 0) {
    // Moving left - check left edge
    uint8_t tile_left_top =
        get_tile(next_x - camera_x, current_y + ENEMY_TOP_MARGIN);
    uint8_t tile_left_bottom =
        get_tile(next_x - camera_x, current_y + ENEMY_HEIGHT - 1);

    if (is_tile_solid(tile_left_top) || is_tile_solid(tile_left_bottom)) {
      // Hit wall, reverse direction
      goomba->vel_x = ENEMY_GOOMBA_SPEED;
      goomba->flip = FALSE;
    } else {
      // Check for cliff (no ground ahead when moving left)
      uint8_t tile_ground_ahead =
          get_tile(next_x - 1 - camera_x, current_y + ENEMY_HEIGHT);
      if (!is_tile_solid(tile_ground_ahead)) {
        // No ground ahead, reverse direction
        goomba->vel_x = ENEMY_GOOMBA_SPEED;
        goomba->flip = FALSE;
      } else {
        // Safe to move
        goomba->x = next_x_upscaled;
      }
    }
  }

  // Apply gravity if not on ground
  uint16_t ground_check_x = goomba->x >> 4;
  uint16_t ground_check_y = (goomba->y >> 4) + ENEMY_HEIGHT;

  uint8_t tile_ground_left =
      get_tile(ground_check_x - camera_x, ground_check_y);
  uint8_t tile_ground_right =
      get_tile(ground_check_x + ENEMY_WIDTH - 1 - camera_x, ground_check_y);

  if (!is_tile_solid(tile_ground_left) && !is_tile_solid(tile_ground_right)) {
    // No ground beneath, apply gravity
    goomba->vel_y = ENEMY_GRAVITY;
  } else {
    // On ground, stop falling
    goomba->vel_y = 0;
    // Snap to ground level
    uint16_t ground_y = ((ground_check_y + 7) & ~7) - ENEMY_HEIGHT;
    goomba->y = ground_y << 4;
  }

  // Vertical movement
  if (goomba->vel_y != 0) {
    next_y_upscaled = goomba->y + goomba->vel_y;
    next_y = next_y_upscaled >> 4;

    if (goomba->vel_y > 0) {
      // Falling down - check for ground collision
      uint8_t tile_bottom_left =
          get_tile(ground_check_x - camera_x, next_y + ENEMY_HEIGHT);
      uint8_t tile_bottom_right = get_tile(
          ground_check_x + ENEMY_WIDTH - 1 - camera_x, next_y + ENEMY_HEIGHT);

      if (is_tile_solid(tile_bottom_left) || is_tile_solid(tile_bottom_right)) {
        // Hit ground, stop falling
        goomba->vel_y = 0;
        goomba->y = (((next_y + ENEMY_HEIGHT + 7) & ~7) - ENEMY_HEIGHT) << 4;
      } else {
        // Continue falling
        goomba->y = next_y_upscaled;
      }
    }
  }
}

void enemy_update(void) {
  uint8_t index_enemy = 0;
  while (index_enemy < enemy_count) {
    enemies[index_enemy].x += enemies[index_enemy].vel_x;
    enemies[index_enemy].y += enemies[index_enemy].vel_y;
    enemies[index_enemy].draw_x =
        (enemies[index_enemy].x - camera_x_upscaled) >> 4;
    enemies[index_enemy].draw_y = enemies[index_enemy].y >> 4;

    // EMU_printf("if %d <= %d\n", enemies[index_enemy].x,  camera_x_upscaled -
    // DEVICE_SCREEN_PX_WIDTH);
    if (enemies[index_enemy].x <= camera_x_upscaled - DEVICE_SCREEN_PX_WIDTH) {
      // EMU_printf("REMOVE ENEMY\n");
      for (uint8_t j = index_enemy; j < enemy_count - 1; j++) {
        enemies[j] = enemies[j + 1];
      }
      enemy_count--;
      hide_sprites_range(1, MAX_HARDWARE_SPRITES);
      continue;
    }

    switch (enemies[index_enemy].type) {
    case ENEMY_GOOMBO:
      enemy_move_goomba(index_enemy);
      // set frame
      if (enemies[index_enemy].frame_counter ==
          ENEMY_LOOP_PER_ANIMATION_FRAME) {
        enemies[index_enemy].frame_counter = 0;
        enemies[index_enemy].flip = !enemies[index_enemy].flip;
      }
      break;
    case ENEMY_KOOPA:
      if (enemies[index_enemy].frame_counter ==
          ENEMY_LOOP_PER_ANIMATION_FRAME) {
        enemies[index_enemy].frame_counter = 0;
        enemies[index_enemy].current_frame =
            (enemies[index_enemy].current_frame + 1) % 2 + 2;
      }
      break;
    }
    enemies[index_enemy].frame_counter++;
    index_enemy++;
  }
}

uint8_t enemy_draw(uint8_t base_sprite) {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(enemies));

  for (int index_enemy = 0; index_enemy < enemy_count; index_enemy++) {
    uint8_t draw_index = enemies[index_enemy].current_frame;
    metasprite_t *enemy_metasprite = enemies_metasprites[draw_index];

    EMU_printf("ENEMY %d %d\n", enemies[index_enemy].draw_x,
               enemies[index_enemy].draw_y);

    if (enemies[index_enemy].flip) {
      base_sprite += move_metasprite_flipx(
          enemy_metasprite, enemies_TILE_ORIGIN, 0, base_sprite,
          enemies[index_enemy].draw_x + DEVICE_SPRITE_PX_OFFSET_X + 4,
          enemies[index_enemy].draw_y + DEVICE_SPRITE_PX_OFFSET_Y +
              enemies_HEIGHT + 8);
    } else {
      base_sprite += move_metasprite_ex(
          enemy_metasprite, enemies_TILE_ORIGIN, 0, base_sprite,
          enemies[index_enemy].draw_x + DEVICE_SPRITE_PX_OFFSET_X + 4,
          enemies[index_enemy].draw_y + DEVICE_SPRITE_PX_OFFSET_Y +
              enemies_HEIGHT + 8);
    }
  }
  SWITCH_ROM(_saved_bank);

  return base_sprite;
}
