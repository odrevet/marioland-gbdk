#ifndef __sound_skid_INCLUDE__
#define __sound_skid_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_skid 0b00000100

BANKREF_EXTERN(sound_skid)
extern const uint8_t sound_skid[];
extern void __mute_mask_sound_skid;

#endif
