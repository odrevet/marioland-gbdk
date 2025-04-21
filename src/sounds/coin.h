#ifndef __coin_INCLUDE__
#define __coin_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_coin 0b00000010

BANKREF_EXTERN(coin)
extern const uint8_t coin[];
extern void __mute_mask_coin;

#endif
