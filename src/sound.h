#ifndef SOUND_H
#define SOUND_H

#include <gb/gb.h>
#include <stdint.h>
#include <stdbool.h>

void sound_init();
void sound_play_jump();
void sound_play_bump();
void sound_play_coin();

#endif