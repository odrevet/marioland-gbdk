#include "hud.h"

void hud_set_level(char major, char minor) {
    char major_str[2] = {major, '\0'};
    char minor_str[2] = {minor, '\0'};
    
    text_print_string_win(12, 1, major_str);
    text_print_string_win(14, 1, minor_str);
  }
  