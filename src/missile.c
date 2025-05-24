#include "missile.h"
#include <stdint.h>

uint8_t missile_count;
missile_t missiles[MISSILE_MAX];


void missile_new(uint16_t x, uint16_t y) {
  if (missile_count < MISSILE_MAX) {
    uint8_t index_missile = 0;
    while (index_missile < MISSILE_MAX) {
      if (missiles[index_missile].active == FALSE) {
        missile_t missile = {
            .x = x << 4, .y = y << 4, .vel_x = 42, .vel_y = 0, .active = TRUE};
        missiles[missile_count] = missile;
        missile_count++;
        break;
      }
      index_missile++;
    }
  }
}

void missile_update(void) {
  for (uint8_t index_missile = 0; index_missile < MISSILE_MAX;
       index_missile++) {
    missiles[index_missile].x += missiles[index_missile].vel_x;
    missiles[index_missile].y += missiles[index_missile].vel_y;
    missiles[index_missile].draw_x =
        (missiles[index_missile].x - camera_x_subpixel) >> 4;
    missiles[index_missile].draw_y = missiles[index_missile].y >> 4;
  }
}

uint8_t missile_draw(uint8_t base_sprite) {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(sprite_common));

  uint8_t draw_index = 11;
  metasprite_t *sprite_common_metasprite =
      sprite_common_metasprites[draw_index];

  for (uint8_t index_missile = 0; index_missile < missile_count;
       index_missile++) {
    base_sprite += move_metasprite_ex(
        sprite_common_metasprite, sprite_common_TILE_ORIGIN, 0, base_sprite,
        missiles[index_missile].draw_x, missiles[index_missile].draw_y);
  }
  SWITCH_ROM(_saved_bank);

  return base_sprite;
}
