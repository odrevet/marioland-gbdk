#include "powerup.h"

powerup_t powerup;

void powerup_new(uint16_t x, uint16_t y, uint8_t type) {}

void powerup_update(void) {}

uint8_t powerup_draw(uint8_t base_sprite) {

    /*uint8_t _saved_bank = _current_bank;
    SWITCH_ROM(BANK(powerup));
  
    uint8_t draw_index = powerup[index_powerup].current_frame;
    metasprite_t *powerup_metasprite = powerup_metasprites[draw_index];

    base_sprite += move_metasprite_ex(
      powerup_metasprite, powerup_TILE_ORIGIN, 0, base_sprite,
      powerup[index_powerup].draw_x, powerup[index_powerup].draw_y);

    SWITCH_ROM(_saved_bank);*/

    return base_sprite;
}
