#ifndef __sound_flag_pole_INCLUDE__
#define __sound_flag_pole_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_flag_pole 0b00000010

BANKREF_EXTERN(sound_flag_pole)
extern const uint8_t sound_flag_pole[];
extern void __mute_mask_sound_flag_pole;

#endif
