#ifndef GAME_H
#define GAME_H

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "textTileset.h"
#include "marioSprites.h"

#include "enemy.h"
#include "global.h"
#include "text.h"
#include "player.h"
#include "pipe.h"

#ifdef NINTENDO
#include "musicmanager.h"
#include "musics.h"
#endif

void init(void) BANKED;
void state_title(void) BANKED;
void state_pause(void) BANKED;
void die(void) BANKED;

#endif