#ifndef GAME_H
#define GAME_H

#include <gb/gb.h>
#include <gbdk/metasprites.h>
#include <gbdk/platform.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics/text.h"
#include "graphics/mario.h"

#include "enemy.h"
#include "global.h"
#include "musics/hUGEDriver.h"
#include "text.h"
#include "player.h"

void init(void);
void state_title(void); 
void state_pause(void); 
void die(void);

#endif