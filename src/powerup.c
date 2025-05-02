#include "powerup.h"

bool powerup_active = FALSE;
powerup_t powerup;

void powerup_new(uint16_t x, uint16_t y, uint8_t type) {
  powerup.x = x;
  powerup.y = y;
  powerup.draw_x = x;
  powerup.draw_y = y;

  powerup.type = type;

  powerup_active = TRUE;
}

void powerup_update(void) {}

uint8_t powerup_draw(uint8_t base_sprite) {
  uint8_t _saved_bank = _current_bank;
  SWITCH_ROM(BANK(sprite_common));

  uint8_t draw_index = 0; // powerup.current_frame;
  metasprite_t *sprite_common_metasprite =
      sprite_common_metasprites[draw_index];

  EMU_printf("DRAW OBJECT %d at %d %d\n", powerup.type, powerup.draw_x, powerup.draw_y);

  base_sprite +=
      move_metasprite_ex(sprite_common_metasprite, sprite_common_TILE_ORIGIN, 0,
                         base_sprite, powerup.draw_x, powerup.draw_y);

  SWITCH_ROM(_saved_bank);

  return base_sprite;
}
