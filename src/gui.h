#ifndef GUI_H
#define GUI_H
#include "player.h"
#include <windows.h>

enum Colors {
  BLACK = 0,
  BLUE = 1,
  GREEN = 2,
  AQUA = 3,
  RED = 4,
  PURPLE = 5,
  YELLOW = 6,
  WHITE = 7,
  GRAY = 8,
  LIGHT_BLUE = 9,
  LIGHT_GREEN = 0xA,  // 0xA ≡ 10
  LIGHT_AQUA = 0xB,   // 0xB ≡ 11
  LIGHT_RED = 0xC,    // 0xC ≡ 12
  LIGHT_PURPLE = 0xD, // 0xD ≡ 13
  LIGHT_YELLOW = 0xE, // 0xE ≡ 14
  BRIGHT_WHITE = 0xF, // 0xF ≡ 15
  DEFAULT = 0x07
};

HANDLE hc;

void welcome(char *version); // gui.h
unsigned short int get_menu(Player *player);
void disp_walking();
void style_printf(const char *format, WORD text_color, ...); // gui.h
unsigned short int get_shop();                               // gui.h
unsigned short int get_ball_shop();                          // gui.h
int get_showcase_choice(int showcase_index);                 // gui.h
void display_encountered(Pokemon *random_pokemon);
void display_player_stats(Player *player);
void display_ball_actions();
void display_styled_ball_type(Ball *ball);
void display_styled_ball_catch_chance(Ball *ball);
void display_styled_ball_info(Ball *ball);

#endif