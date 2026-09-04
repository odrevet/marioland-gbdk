#ifndef GAME_H
#define GAME_H

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <gbdk/platform.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
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

void init(void);
void state_title(void); 
void state_pause(void); 
void die(void);

#endif