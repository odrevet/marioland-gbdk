#include "text.h"
#include "graphics/text.h"

void text_print_char_win(uint8_t x, uint8_t y, unsigned char chr) {
  uint8_t tile;

  if (chr >= '0' && chr <= '9') {
    tile = chr - '0';
  } else {
    switch (chr) {
    case 'A':
      tile = LETTERS_STARTS_AT + 0;
      break;
    case 'B':
      tile = LETTERS_STARTS_AT + 1;
      break;
    case 'C':
      tile = LETTERS_STARTS_AT + 2;
      break;
    case 'D':
      tile = LETTERS_STARTS_AT + 3;
      break;
    case 'E':
      tile = LETTERS_STARTS_AT + 4;
      break;
    case 'F':
      tile = LETTERS_STARTS_AT + 5;
      break;
    case 'G':
      tile = LETTERS_STARTS_AT + 6;
      break;
    case 'H':
      tile = LETTERS_STARTS_AT + 7;
      break;
    case 'I':
      tile = LETTERS_STARTS_AT + 8;
      break;
    case 'K':
      tile = LETTERS_STARTS_AT + 9;
      break;
    case 'L':
      tile = LETTERS_STARTS_AT + 10;
      break;
    case 'M':
      tile = LETTERS_STARTS_AT + 11;
      break;
    case 'N':
      tile = LETTERS_STARTS_AT + 12;
      break;
    case 'O':
      tile = 0; // 0 and O are the same character
      break;
    case 'P':
      tile = LETTERS_STARTS_AT + 13;
      break;
    case 'Q':
      tile = LETTERS_STARTS_AT + 14;
      break;
    case 'R':
      tile = LETTERS_STARTS_AT + 15;
      break;
    case 'S':
      tile = LETTERS_STARTS_AT + 16;
      break;
    case 'T':
      tile = LETTERS_STARTS_AT + 17;
      break;
    case 'U':
      tile = LETTERS_STARTS_AT + 18;
      break;
    case 'V':
      tile = LETTERS_STARTS_AT + 19;
      break;
    case 'W':
      tile = LETTERS_STARTS_AT + 20;
      break;
    case 'Y':
      tile = LETTERS_STARTS_AT + 21;
      break;
    case 'Z':
      tile = LETTERS_STARTS_AT + 22;
      break;
    case 'x':
      tile = LETTERS_STARTS_AT + 23;
      break;
    case '-':
      tile = LETTERS_STARTS_AT + 24;
      break;
    case '.':
      tile = LETTERS_STARTS_AT + 25;
      break;
    case ',':
      tile = LETTERS_STARTS_AT + 26;
      break;
    case '!':
      tile = LETTERS_STARTS_AT + 27;
      break;
    case '?':
      tile = LETTERS_STARTS_AT + 28;
      break;
    case ' ':
    default:
      tile = LETTERS_STARTS_AT + 29;
    }
  }

  set_win_tile_xy(x, y, tile + text_TILE_ORIGIN);
}

void text_print_string_win(uint8_t x, uint8_t y, unsigned char *string) {
  uint8_t offset_x = 0;
  uint8_t offset_y = 0;

  while (string[0]) {
    if (string[0] == '\n') {
      offset_x = 0;
      offset_y++;
    } else {
      text_print_char_win(x + offset_x, y + offset_y, (unsigned char)string[0]);
      offset_x++;
    }

    string += 1;
  }
}
