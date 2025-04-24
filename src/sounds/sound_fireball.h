#ifndef __sound_fireball_INCLUDE__
#define __sound_fireball_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_fireball 0b00000010

BANKREF_EXTERN(sound_fireball)
extern const uint8_t sound_fireball[];
extern void __mute_mask_sound_fireball;

#endif
