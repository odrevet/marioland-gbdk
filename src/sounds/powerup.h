#ifndef __powerup_INCLUDE__
#define __powerup_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_powerup 0b00000010

BANKREF_EXTERN(powerup)
extern const uint8_t powerup[];
extern void __mute_mask_powerup;

#endif
