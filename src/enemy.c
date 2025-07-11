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
          enemies[index_enemy].draw_y + DEVICE_SPRITE_PX_OFFSET_Y + enemies_HEIGHT + 8);
    } else {
      base_sprite += move_metasprite_ex(
          enemy_metasprite, enemies_TILE_ORIGIN, 0, base_sprite,
          enemies[index_enemy].draw_x + DEVICE_SPRITE_PX_OFFSET_X + 4,
          enemies[index_enemy].draw_y + DEVICE_SPRITE_PX_OFFSET_Y + enemies_HEIGHT + 8);
    }
  }
  SWITCH_ROM(_saved_bank);

  return base_sprite;
}
