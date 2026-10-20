#ifndef HUD_H
#define HUD_H

#include <gbdk/platform.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "text.h"


void hud_set_level(uint8_t major, uint8_t minor);
void hud_update_coins(void);
void hud_update_score(void);
void hud_update_time(void);
void hud_update_lives(void);

#endif