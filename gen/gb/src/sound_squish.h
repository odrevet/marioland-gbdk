#ifndef __sound_squish_INCLUDE__
#define __sound_squish_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_squish 0b00000010

BANKREF_EXTERN(sound_squish)
extern const uint8_t sound_squish[];
extern void __mute_mask_sound_squish;

#endif
