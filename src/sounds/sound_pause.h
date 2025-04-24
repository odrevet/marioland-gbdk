#ifndef __sound_pause_INCLUDE__
#define __sound_pause_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_pause 0b00000010

BANKREF_EXTERN(sound_pause)
extern const uint8_t sound_pause[];
extern void __mute_mask_sound_pause;

#endif
