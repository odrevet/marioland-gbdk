#include "enemy.h"
#include <stdint.h>

uint8_t enemy_count = 0;
enemy_t enemies[ENEMY_MAX];

void enemy_new(uint16_t x, uint16_t y, uint8_t type) {
  if (enemy_count < ENEMY_MAX) {
    uint8_t current_frame;
    int16_t vel_x;
    switch (type) {
    case ENEMY_TYPE_GOOMBA:
      current_frame = 0;
      vel_x = -8;
      break;
    case ENEMY_TYPE_KOOPA:
      current_frame = 2;
      vel_x = -10;
      break;
    }
    enemy_t enemy = {.x = x,
                     .y = y,
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

void enemy_update() {
  for (uint8_t index_enemy = 0; index_enemy < enemy_count; index_enemy++) {
    enemies[index_enemy].x += enemies[index_enemy].vel_x;

    switch (enemies[index_enemy].type) {
    case ENEMY_TYPE_GOOMBA:
      if (enemies[index_enemy].frame_counter ==
          ENEMY_LOOP_PER_ANIMATION_FRAME) {
        enemies[index_enemy].frame_counter = 0;
        enemies[index_enemy].flip = !enemies[index_enemy].flip;
      }
      break;
    case ENEMY_TYPE_KOOPA:
      if (enemies[index_enemy].frame_counter ==
          ENEMY_LOOP_PER_ANIMATION_FRAME) {
        enemies[index_enemy].frame_counter = 0;
        enemies[index_enemy].current_frame =
            (enemies[index_enemy].current_frame + 1) % 2 + 2;
      }
      break;
    }
    enemies[index_enemy].frame_counter++;
  }
}

void enemy_draw(int start) {
  /*for (int index_enemy = 0; index_enemy < enemy_count; index_enemy++) {
    uint16_t draw_x = enemies[index_enemy].x >> 4;
    int enemy_draw_x_camera_offset = draw_x - camera_x;
    uint8_t draw_index = enemies[index_enemy].current_frame;
    metasprite_t *enemy_metasprite = enemies_metasprites[draw_index];

    if (enemies[index_enemy].flip) {
      move_metasprite_vflip(enemy_metasprite, start, start + index_enemy * 4,
                            enemy_draw_x_camera_offset, enemies[index_enemy].y);
    } else {
      move_metasprite(enemy_metasprite, start, start + index_enemy * 4,
                      enemy_draw_x_camera_offset, enemies[index_enemy].y);
    }
  }*/
}