#ifndef __sound_bowser_fire_INCLUDE__
#define __sound_bowser_fire_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_bowser_fire 0b00001000

BANKREF_EXTERN(sound_bowser_fire)
extern const uint8_t sound_bowser_fire[];
extern void __mute_mask_sound_bowser_fire;

#endif
