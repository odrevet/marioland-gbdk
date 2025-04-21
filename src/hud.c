#include "hud.h"

void hud_set_level(char major, char minor) {
    char major_str[2] = {major, '\0'};
    char minor_str[2] = {minor, '\0'};
    
    text_print_string_win(12, 1, major_str);
    text_print_string_win(14, 1, minor_str);
  }
  
  void hud_update_coins(void) {
    char coins_str[3];
  
    if (coins < 10) {
      coins_str[0] = '0'; // Add leading zero
      itoa(coins, coins_str + 1, 10);
    } else {
      itoa(coins, coins_str, 10);
    }
  
    text_print_string_win(9, 1, coins_str);
  }
  
  void hud_update_score(void) {
    char score_str[5];
    itoa(score, score_str, 10);
    text_print_string_win(3, 1, score_str);
  }
  
  void hud_update_time(void) {
    char time_str[4];
    itoa(time / 40, time_str, 10);
    text_print_string_win(DEVICE_SCREEN_WIDTH - 3, 1, "000");
    text_print_string_win(DEVICE_SCREEN_WIDTH - strlen(time_str), 1, time_str);
  }
  
  void hud_update_lives(void) {
    char lives_str[4];
    itoa(lives, lives_str, 10);
    text_print_string_win(7, 0, lives_str);
  }

