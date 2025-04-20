#ifndef HUD_H
#define HUD_H

#include <gb/gb.h>
#include <gb/metasprites.h>
#include <gbdk/platform.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics/enemies.h"
#include "graphics/text.h"
#include "graphics/mario.h"

#include "enemy.h"
#include "global.h"
#include "graphics/text.h"
#include "hUGEDriver.h"
#include "sound.h"
#include "text.h"


void hud_set_level(char major, char minor);

#endif