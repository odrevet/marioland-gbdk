#ifndef __skid_INCLUDE__
#define __skid_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_skid 0b00000100

BANKREF_EXTERN(skid)
extern const uint8_t skid[];
extern void __mute_mask_skid;

#endif
