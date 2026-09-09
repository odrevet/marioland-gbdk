#ifndef __sound_bump_INCLUDE__
#define __sound_bump_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_bump 0b00000010

BANKREF_EXTERN(sound_bump)
extern const uint8_t sound_bump[];
extern void __mute_mask_sound_bump;

#endif
