#include "coin_animated.h"
#include "gb/gb.h"
#include "level.h"
#include <stdint.h>

coin_animated_t coin_animated_array[NB_COIN_ANIMATED];
uint8_t coin_index = 0;

void coin_animated_new(uint8_t index_x, uint8_t index_y) {
  coin_animated_array[coin_index].draw_x = index_x << 3;
  coin_animated_array[coin_index].draw_y = index_y << 3;
  coin_animated_array[coin_index].ttl = COIN_ANIMATED_INITIAL_TTL;
  hide_sprite(10 + coin_index);
  coin_animated_array[coin_index].hw_sprite_index = 10 + coin_index;
  coin_index = (coin_index + 1) % NB_COIN_ANIMATED;
}

void coin_animated_update(void) {
  uint8_t i;

  for (i = 0; i < NB_COIN_ANIMATED; i++) {
    if (coin_animated_array[i].ttl > 0) {
      coin_animated_array[i].ttl--;
      coin_animated_array[i].draw_y--;
      if (coin_animated_array[i].ttl == 0) {
        hide_sprite(coin_animated_array[i].hw_sprite_index);
      }
    }
  }
}

uint8_t coin_animated_draw(uint8_t base_sprite) {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(sprite_common));

  uint8_t i;

  for (i = 0; i < NB_COIN_ANIMATED; i++) {
    if (coin_animated_array[i].ttl > 0) {
      uint8_t draw_index = 3 + ((20 - coin_animated_array[i].ttl) % 3) * 5;

      metasprite_t *sprite_common_metasprite =
          sprite_common_metasprites[draw_index];

      base_sprite += move_metasprite_ex(
          sprite_common_metasprite, sprite_common_TILE_ORIGIN, 0, coin_animated_array[i].hw_sprite_index,
          coin_animated_array[i].draw_x + 12 - camera_x,
          coin_animated_array[i].draw_y + 32);
    }
  }

  SWITCH_ROM(_saved_bank);

  return base_sprite;
}
