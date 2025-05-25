#include "missile.h"
#include "gb/gb.h"
#include "level.h"
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
    if (missiles[index_missile].active) {
      missiles[index_missile].x += missiles[index_missile].vel_x;
      missiles[index_missile].y += missiles[index_missile].vel_y;
      missiles[index_missile].draw_x = (missiles[index_missile].x) >> 4;
      missiles[index_missile].draw_y = missiles[index_missile].y >> 4;

      EMU_printf("Missile X position is %d. Draw X is %d\n",
                 missiles[index_missile].x, missiles[index_missile].draw_x);
      if (missiles[index_missile].draw_x >= 255) {
        missiles[index_missile].active = FALSE;
        missile_count--;
        // hide_sprites_range(1, MAX_HARDWARE_SPRITES);
      } else {
        uint8_t index_x =
            TILE_INDEX_X(missiles[index_missile].draw_x, camera_x);
        uint8_t index_y = TILE_INDEX_Y(missiles[index_missile].draw_y);
        uint8_t index_map_buffer =
            index_y * DEVICE_SCREEN_BUFFER_WIDTH + index_x;
        if (map_buffer[index_map_buffer] == BREAKABLE_BLOCK) {
          // update map buffer and vram with an empty tile
          map_buffer[index_map_buffer] = TILE_EMPTY;
          set_bkg_tile_xy(index_x, index_y, TILE_EMPTY);

          missiles[index_missile].active = FALSE;
          missile_count--;
        }
      }
    }
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
    if (missiles[index_missile].active) {
      base_sprite += move_metasprite_ex(
          sprite_common_metasprite, sprite_common_TILE_ORIGIN, 0, base_sprite,
          missiles[index_missile].draw_x + DEVICE_SPRITE_PX_OFFSET_X,
          missiles[index_missile].draw_y + DEVICE_SPRITE_PX_OFFSET_Y);
    }
  }
  SWITCH_ROM(_saved_bank);

  return base_sprite;
}
