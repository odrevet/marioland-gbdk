#ifndef __sound_destroyed_INCLUDE__
#define __sound_destroyed_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_destroyed 0b00001000

BANKREF_EXTERN(sound_destroyed)
extern const uint8_t sound_destroyed[];
extern void __mute_mask_sound_destroyed;

#endif
