#ifndef __flag_pole_INCLUDE__
#define __flag_pole_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_flag_pole 0b00000010

BANKREF_EXTERN(flag_pole)
extern const uint8_t flag_pole[];
extern void __mute_mask_flag_pole;

#endif
