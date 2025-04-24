#ifndef __sound_skid_alt_INCLUDE__
#define __sound_skid_alt_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_skid_alt 0b00000010

BANKREF_EXTERN(sound_skid_alt)
extern const uint8_t sound_skid_alt[];
extern void __mute_mask_sound_skid_alt;

#endif
