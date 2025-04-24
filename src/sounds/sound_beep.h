#ifndef __sound_beep_INCLUDE__
#define __sound_beep_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_beep 0b00000010

BANKREF_EXTERN(sound_beep)
extern const uint8_t sound_beep[];
extern void __mute_mask_sound_beep;

#endif
