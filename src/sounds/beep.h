#ifndef __beep_INCLUDE__
#define __beep_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_beep 0b00000010

BANKREF_EXTERN(beep)
extern const uint8_t beep[];
extern void __mute_mask_beep;

#endif
