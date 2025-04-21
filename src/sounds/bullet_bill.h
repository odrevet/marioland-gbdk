#ifndef __bullet_bill_INCLUDE__
#define __bullet_bill_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define MUTE_MASK_bullet_bill 0b00000010

BANKREF_EXTERN(bullet_bill)
extern const uint8_t bullet_bill[];
extern void __mute_mask_bullet_bill;

#endif
