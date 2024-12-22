#ifndef TEXT_H
#define TEXT_H

#include <gb/gb.h>
#include "graphics/text.h"

#define LETTERS_STARTS_AT 10

void text_print_char_win(uint8_t x, uint8_t y, unsigned char chr);
void text_print_string_win(uint8_t x, uint8_t y, unsigned char *string);

#endif
