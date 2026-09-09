#ifndef __sound_powerup_INCLUDE__
#define __sound_powerup_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_sound_powerup 0b00000010

BANKREF_EXTERN(sound_powerup)
extern const uint8_t sound_powerup[];
extern void __mute_mask_sound_powerup;

#endif
