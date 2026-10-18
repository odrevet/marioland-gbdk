#include "coin_animated.h"
#include <gbdk/platform.h>
#include "level.h"
#include <stdint.h>

coin_animated_t coin_animated_array[NB_COIN_ANIMATED];
uint8_t coin_index = 0;

void coin_animated_new(uint8_t index_x, uint8_t index_y) {
  coin_animated_array[coin_index].draw_x = index_x << 3;
  coin_animated_array[coin_index].draw_y = index_y << 3;
  coin_animated_array[coin_index].ttl = COIN_ANIMATED_INITIAL_TTL;
  coin_animated_array[coin_index].anim_frame = 0;
  hide_sprite(COIN_HW_SPRITE_BASE + coin_index);
  coin_animated_array[coin_index].hw_sprite_index = COIN_HW_SPRITE_BASE + coin_index;
  coin_index++;
  if (coin_index >= NB_COIN_ANIMATED) {
    coin_index = 0;
  }
}

void coin_animated_update(void) {
  uint8_t i;

  for (i = 0; i < NB_COIN_ANIMATED; i++) {
    coin_animated_t *coin = &coin_animated_array[i];

    if (coin->ttl > 0) {
      coin->ttl--;
      coin->draw_y--;
      coin->anim_frame++;
      if (coin->anim_frame >= 3) {
        coin->anim_frame = 0;
      }
      if (coin->ttl == 0) {
        hide_sprite(coin->hw_sprite_index);
      }
    }
  }
}

uint8_t coin_animated_draw(uint8_t base_sprite) {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(commonSprites));

  uint8_t i;

  for (i = 0; i < NB_COIN_ANIMATED; i++) {
    coin_animated_t *coin = &coin_animated_array[i];

    if (coin->ttl > 0) {
      uint8_t draw_index = 3 + coin->anim_frame * 5;

      metasprite_t *commonSprites_metasprite =
          commonSprites_metasprites[draw_index];

      base_sprite += move_metasprite_ex(
          commonSprites_metasprite, commonSprites_TILE_ORIGIN, 0, coin->hw_sprite_index,
          coin->draw_x + 12 - camera_x,
          coin->draw_y + 32);
    }
  }

  SWITCH_ROM(_saved_bank);

  return base_sprite;
}
