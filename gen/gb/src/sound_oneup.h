#ifndef __sound_oneup_INCLUDE__
#define __sound_oneup_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_oneup 0b00000010

BANKREF_EXTERN(sound_oneup)
extern const uint8_t sound_oneup[];
extern void __mute_mask_sound_oneup;

#endif
