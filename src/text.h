#ifndef TEXT_H
#define TEXT_H

#include <gbdk/platform.h>
#include "textTileset.h"

#define LETTERS_STARTS_AT 10

void text_print_char(uint8_t x, uint8_t y, unsigned char chr) BANKED;
// Kept in the home bank so the string is read in the caller's bank. A banked
// implementation would read caller string literals from its own bank, which
// shows up as "?" on the HUD.
void text_print_string(uint8_t x, uint8_t y, unsigned char *string) NONBANKED;

#endif
