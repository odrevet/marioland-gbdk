#ifndef __sound_kick_INCLUDE__
#define __sound_kick_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_kick 0b00000010

BANKREF_EXTERN(sound_kick)
extern const uint8_t sound_kick[];
extern void __mute_mask_sound_kick;

#endif
