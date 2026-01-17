#pragma bank 255

#include "enemy.h"
#include "global.h"
#include "level.h"
#include <stdint.h>

uint8_t enemy_count = 0;
enemy_t enemies[ENEMY_MAX];

BANKREF(enemy)

#include <gbdk/emu_debug.h>

// Constants
#define ENEMY_WIDTH 8
#define ENEMY_HEIGHT 16
#define ENEMY_TOP_MARGIN 0
#define ENEMY_GRAVITY 32
#define ENEMY_GOOMBA_SPEED 4
#define ENEMY_KOOPA_SPEED 4
#define ENEMY_FLY_WAIT_FRAMES 60
#define ENEMY_FLY_JUMP_VELOCITY -48
#define ENEMY_FLY_JUMP_SPEED 8

// Helper function: Check if enemy has solid ground beneath
uint8_t enemy_has_ground(enemy_t *enemy) BANKED {
  uint16_t ground_check_x = enemy->x >> 4;
  uint16_t ground_check_y = (enemy->y >> 4) + ENEMY_HEIGHT;

  uint8_t tile_ground_left = get_tile(ground_check_x - camera_x, ground_check_y);
  uint8_t tile_ground_right = get_tile(ground_check_x + ENEMY_WIDTH - 1 - camera_x, ground_check_y);

  return is_tile_solid(tile_ground_left) || is_tile_solid(tile_ground_right);
}

// Helper function: Check if there's ground ahead (for cliff detection)
uint8_t enemy_has_ground_ahead(enemy_t *enemy, int8_t vel_x) BANKED {
  uint16_t current_x = enemy->x >> 4;
  uint16_t current_y = enemy->y >> 4;
  
  if (vel_x > 0) {
    // Moving right - check one tile ahead
    uint8_t tile = get_tile(current_x + ENEMY_WIDTH - camera_x, current_y + ENEMY_HEIGHT);
    return is_tile_solid(tile);
  } else if (vel_x < 0) {
    // Moving left - check one tile ahead
    uint8_t tile = get_tile(current_x - 1 - camera_x, current_y + ENEMY_HEIGHT);
    return is_tile_solid(tile);
  }
  return FALSE;
}

// Helper function: Apply horizontal movement with wall collision
void enemy_apply_horizontal_movement(enemy_t *enemy, uint8_t check_cliffs) BANKED {
  if (enemy->vel_x == 0) return;

  uint16_t next_x_upscaled = enemy->x + enemy->vel_x;
  uint16_t next_x = next_x_upscaled >> 4;
  uint16_t current_x = enemy->x >> 4;
  uint16_t current_y = enemy->y >> 4;

  uint8_t hit_wall = FALSE;
  uint8_t hit_cliff = FALSE;

  if (enemy->vel_x > 0) {
    // Moving right - check right edge for wall
    uint8_t tile_right_top = get_tile(next_x + ENEMY_WIDTH - 1 - camera_x, current_y + ENEMY_TOP_MARGIN);
    uint8_t tile_right_bottom = get_tile(next_x + ENEMY_WIDTH - 1 - camera_x, current_y + ENEMY_HEIGHT - 1);

    hit_wall = is_tile_solid(tile_right_top) || is_tile_solid(tile_right_bottom);
    
    if (check_cliffs && !hit_wall) {
      hit_cliff = !enemy_has_ground_ahead(enemy, enemy->vel_x);
    }
  } else if (enemy->vel_x < 0) {
    // Moving left - check left edge for wall
    uint8_t tile_left_top = get_tile(next_x - camera_x, current_y + ENEMY_TOP_MARGIN);
    uint8_t tile_left_bottom = get_tile(next_x - camera_x, current_y + ENEMY_HEIGHT - 1);

    hit_wall = is_tile_solid(tile_left_top) || is_tile_solid(tile_left_bottom);
    
    if (check_cliffs && !hit_wall) {
      hit_cliff = !enemy_has_ground_ahead(enemy, enemy->vel_x);
    }
  }

  if (hit_wall || hit_cliff) {
    // Reverse direction
    enemy->vel_x = -enemy->vel_x;
    enemy->flip = !enemy->flip;
  } else {
    // Safe to move
    enemy->x = next_x_upscaled;
  }
}

// Helper function: Apply gravity and vertical movement
void enemy_apply_vertical_movement(enemy_t *enemy, int8_t gravity_divisor) BANKED {
  uint16_t ground_check_x = enemy->x >> 4;
  uint16_t ground_check_y = (enemy->y >> 4) + ENEMY_HEIGHT;

  uint8_t on_ground = enemy_has_ground(enemy);

  // Apply gravity when not on ground
  if (!on_ground) {
    if (gravity_divisor == 1) {
      enemy->vel_y = ENEMY_GRAVITY;
    } else {
      enemy->vel_y += ENEMY_GRAVITY / gravity_divisor;
    }
  }

  // Apply vertical movement
  if (enemy->vel_y != 0) {
    uint16_t next_y_upscaled = enemy->y + enemy->vel_y;
    uint16_t next_y = next_y_upscaled >> 4;

    if (enemy->vel_y > 0) {
      // Falling down - check for ground collision
      uint8_t tile_bottom_left = get_tile(ground_check_x - camera_x, next_y + ENEMY_HEIGHT);
      uint8_t tile_bottom_right = get_tile(ground_check_x + ENEMY_WIDTH - 1 - camera_x, next_y + ENEMY_HEIGHT);

      if (is_tile_solid(tile_bottom_left) || is_tile_solid(tile_bottom_right)) {
        // Hit ground, stop falling
        enemy->vel_y = 0;
        enemy->y = (((next_y + ENEMY_HEIGHT + 7) & ~7) - ENEMY_HEIGHT) << 4;
      } else {
        // Continue falling
        enemy->y = next_y_upscaled;
      }
    } else if (enemy->vel_y < 0) {
      // Moving up - check for ceiling collision
      uint8_t tile_top_left = get_tile(ground_check_x - camera_x, next_y + ENEMY_TOP_MARGIN);
      uint8_t tile_top_right = get_tile(ground_check_x + ENEMY_WIDTH - 1 - camera_x, next_y + ENEMY_TOP_MARGIN);

      if (is_tile_solid(tile_top_left) || is_tile_solid(tile_top_right)) {
        // Hit ceiling, start falling
        enemy->vel_y = 0;
      } else {
        // Continue moving up
        enemy->y = next_y_upscaled;
      }
    }
  }
}

void enemy_new(uint16_t x, uint16_t y, uint8_t type) NONBANKED {
  EMU_printf("enemy new at %d %d\n", x, y);

  // Find first inactive enemy slot
  for (uint8_t i = 0; i < ENEMY_MAX; i++) {
    if (!enemies[i].active) {
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

      enemies[i].x = x << 4;
      enemies[i].y = y << 4;
      enemies[i].vel_x = vel_x;
      enemies[i].vel_y = 0;
      enemies[i].type = type;
      enemies[i].frame_counter = 0;
      enemies[i].current_frame = current_frame;
      enemies[i].flip = FALSE;
      enemies[i].stomped = FALSE;
      enemies[i].stomped_timer = 0;
      enemies[i].active = TRUE;

      enemy_count++;
      return;
    }
  }
}

void enemy_move_goomba(uint8_t index) BANKED {
  enemy_t *goomba = &enemies[index];

  // Don't move if stomped or inactive
  if (goomba->stomped || !goomba->active) {
    return;
  }

  // Set initial velocity if not moving
  if (goomba->vel_x == 0) {
    goomba->vel_x = -ENEMY_GOOMBA_SPEED; // Start moving left
  }

  // Apply movement
  enemy_apply_horizontal_movement(goomba, FALSE); // Goombas don't avoid cliffs
  enemy_apply_vertical_movement(goomba, 1); // Full gravity
}

void enemy_move_koopa(uint8_t index) BANKED {
  enemy_t *koopa = &enemies[index];

  // Don't move if stomped or inactive
  if (koopa->stomped || !koopa->active) {
    return;
  }

  // Set initial velocity if not moving
  if (koopa->vel_x == 0) {
    koopa->vel_x = -ENEMY_KOOPA_SPEED; // Start moving left
  }

  // Apply movement
  enemy_apply_horizontal_movement(koopa, TRUE); // Koopas turn at cliffs
  enemy_apply_vertical_movement(koopa, 1); // Full gravity
}

void enemy_move_fly(uint8_t index) BANKED {
  enemy_t *fly = &enemies[index];

  // Don't move if stomped or inactive
  if (fly->stomped || !fly->active) {
    return;
  }

  uint8_t on_ground = enemy_has_ground(fly);

  // Check if it's time to jump
  if (on_ground && fly->frame_counter >= ENEMY_FLY_WAIT_FRAMES) {
    EMU_printf("FLY Time to jump!\n");
    fly->vel_y = ENEMY_FLY_JUMP_VELOCITY;
    fly->vel_x = ENEMY_FLY_JUMP_SPEED; // Move horizontally when jumping
    fly->frame_counter = 0; // Reset counter
  }

  // Stop horizontal movement when landing
  if (on_ground && fly->vel_y == 0) {
    fly->vel_x = 0;
  }

  // Apply movement
  enemy_apply_horizontal_movement(fly, FALSE); // No cliff checking for flies
  enemy_apply_vertical_movement(fly, 8); // Lighter gravity (1/8th)

  EMU_printf("FLY vel %d %d\n", fly->vel_x, fly->vel_y);
}

void enemy_stomp(uint8_t index_enemy) NONBANKED {
  EMU_printf("STOMP ENEMY %d\n", index_enemy);

  enemy_t *enemy = &enemies[index_enemy];

  if (!enemy->active) {
    return;
  }

  // Mark as stomped
  enemy->stomped = TRUE;
  enemy->stomped_timer = ENEMY_STOMPED_DISPLAY_FRAMES;

  // Stop all movement
  enemy->vel_x = 0;
  enemy->vel_y = 0;

  // Set to stomped/crushed sprite frame
  switch (enemy->type) {
  case ENEMY_GOOMBO:
    enemy->current_frame = 1;
    enemy->flip = FALSE;
    break;
  case ENEMY_KOOPA:
    enemy->current_frame = 4;
    break;
  default:
    enemy->current_frame++;
    break;
  }
}

void enemy_remove(uint8_t index_enemy) NONBANKED {
  EMU_printf("REMOVE ENEMY %d\n", index_enemy);

  if (index_enemy < ENEMY_MAX && enemies[index_enemy].active) {
    enemies[index_enemy].active = FALSE;
    enemy_count--;
    hide_sprites_range(1, MAX_HARDWARE_SPRITES);
  }
}

void enemy_reset_all(void) NONBANKED {
  EMU_printf("RESET ALL ENEMIES\n");

  // Deactivate all enemy slots
  for (uint8_t i = 0; i < ENEMY_MAX; i++) {
    enemies[i].active = FALSE;
    enemies[i].stomped = FALSE;
    enemies[i].x = 0;
    enemies[i].y = 0;
    enemies[i].vel_x = 0;
    enemies[i].vel_y = 0;
    enemies[i].draw_x = 0;
    enemies[i].draw_y = 0;
  }

  // Reset enemy count
  enemy_count = 0;

  // Hide all enemy sprites
  hide_sprites_range(1, MAX_HARDWARE_SPRITES);
}

void enemy_update(void) NONBANKED {
  for (uint8_t index_enemy = 0; index_enemy < ENEMY_MAX; index_enemy++) {
    // Skip inactive enemies
    if (!enemies[index_enemy].active) {
      continue;
    }

    // Handle stomped enemies
    if (enemies[index_enemy].stomped) {
      enemies[index_enemy].stomped_timer--;
      if (enemies[index_enemy].stomped_timer == 0) {
        // Timer expired, remove the enemy
        enemy_remove(index_enemy);
        continue;
      }
      // Update draw position for scrolling (same as normal enemies)
      enemies[index_enemy].draw_x =
          (enemies[index_enemy].x - camera_x_upscaled) >> 4;
      enemies[index_enemy].draw_y = enemies[index_enemy].y >> 4;
      continue;
    }

    // Update based on enemy type
    uint8_t _saved_bank = _current_bank;

    switch (enemies[index_enemy].type) {
    case ENEMY_GOOMBO:
      SWITCH_ROM(BANK(enemy));
      enemy_move_goomba(index_enemy);
      SWITCH_ROM(_saved_bank);
      // Set frame animation (only when not stomped)
      if (enemies[index_enemy].frame_counter == ENEMY_LOOP_PER_ANIMATION_FRAME) {
        enemies[index_enemy].frame_counter = 0;
        enemies[index_enemy].flip = !enemies[index_enemy].flip;
      }
      break;
    case ENEMY_KOOPA:
      SWITCH_ROM(BANK(enemy));
      enemy_move_koopa(index_enemy);
      SWITCH_ROM(_saved_bank);
      if (enemies[index_enemy].frame_counter == ENEMY_LOOP_PER_ANIMATION_FRAME) {
        enemies[index_enemy].frame_counter = 0;
        enemies[index_enemy].current_frame =
            (enemies[index_enemy].current_frame + 1) % 2 + 2;
      }
      break;
    case ENEMY_FLY:
      SWITCH_ROM(BANK(enemy));
      enemy_move_fly(index_enemy);
      SWITCH_ROM(_saved_bank);
      // TODO: Add wing flapping animation
      break;
    }

    // Update draw position AFTER movement
    enemies[index_enemy].draw_x =
        (enemies[index_enemy].x - camera_x_upscaled) >> 4;
    enemies[index_enemy].draw_y = enemies[index_enemy].y >> 4;

    // Remove if off-screen to the left
    if (camera_x_upscaled > DEVICE_SCREEN_PX_WIDTH &&
        enemies[index_enemy].x <= camera_x_upscaled - DEVICE_SCREEN_PX_WIDTH) {
      enemy_remove(index_enemy);
      continue;
    }

    enemies[index_enemy].frame_counter++;
  }
}

uint8_t enemy_draw(uint8_t base_sprite) NONBANKED {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(enemies));

  for (uint8_t index_enemy = 0; index_enemy < ENEMY_MAX; index_enemy++) {
    // Skip inactive enemies
    if (!enemies[index_enemy].active) {
      continue;
    }

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