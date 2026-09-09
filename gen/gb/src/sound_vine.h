#ifndef __sound_vine_INCLUDE__
#define __sound_vine_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_vine 0b00000010

BANKREF_EXTERN(sound_vine)
extern const uint8_t sound_vine[];
extern void __mute_mask_sound_vine;

#endif
