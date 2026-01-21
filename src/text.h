#ifndef TEXT_H
#define TEXT_H

#include <gbdk/platform.h>
#include "graphics/text.h"

#define LETTERS_STARTS_AT 10

void text_print_char(uint8_t x, uint8_t y, unsigned char chr);
void text_print_string(uint8_t x, uint8_t y, unsigned char *string);

#endif
