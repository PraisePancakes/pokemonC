#include "gui.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void welcome(char *version) {
  SetConsoleTextAttribute(hc, YELLOW | FOREGROUND_INTENSITY);
  printf("\n =-=-=-= WELCOME TO POKEMON C %s =-=-=-= \n", version);
  style_printf(
    WHITE,
    "Pokemon C is a pokemon simulator\n[] catch pokemons\n[] showcase your pokemons\npress any key to advance...");
  getch();
}

unsigned short int get_menu(Player *player) {
  unsigned short int option = 0;
  style_printf(YELLOW, "\n =-=-= POKEMON C =-=-=\t\t\t");
  SetConsoleTextAttribute(hc, BLUE | FOREGROUND_INTENSITY);
  printf(
    "USER { username : %s, id : %s, xp : %hu, points : %hu, showcase : [%s :: %s] "
    "}\n ",
    player->username,
    player->id,
    player->xp,
    player->points,
    player->showcase,
    player->showcase_type);
  style_printf(BRIGHT_WHITE,
               "1 : CATCH \n 2 : SHOWCASE \n 3 : ITEM SHOP \n 4 : EXIT \n");

  scanf("%hu", &option);
  return option;
}

void disp_walking() {
  const unsigned short int MAX_SLEEP_INTERVAL = 4;
  unsigned short int random_sleep_interval = rand() % MAX_SLEEP_INTERVAL;
  bool _done_walking = false;
  while (!_done_walking) {
    sleep(1);
    printf("Walking... \n");
    sleep(1);
    printf("Walking... \n");
    sleep(MAX_SLEEP_INTERVAL);
    _done_walking = true;
  }
}

void style_printf_encountered(WORD text_color, Pokemon *pokemon) {
  SetConsoleTextAttribute(hc, text_color | FOREGROUND_INTENSITY);
  printf("** YOU ENCOUNTERED : %s **\n", pokemon->name);
  SetConsoleTextAttribute(hc, DEFAULT);
}

void style_printf_fled(WORD text_color, Pokemon *pokemon) {
  SetConsoleTextAttribute(hc, text_color | FOREGROUND_INTENSITY);
  printf("** YOU RAN AWAY :: %s FLED ** \n", pokemon->name);
  SetConsoleTextAttribute(hc, DEFAULT);
}

void style_printf(WORD text_color, char *string) {
  SetConsoleTextAttribute(hc, text_color | FOREGROUND_INTENSITY);
  printf("%s", string);
  SetConsoleTextAttribute(hc, DEFAULT);
};

void style_printf_points(WORD text_color, Player *player) {
  style_printf(BRIGHT_WHITE, "[ YOU HAVE ");
  SetConsoleTextAttribute(hc, text_color | FOREGROUND_INTENSITY);
  printf("%hu ", player->points);
  SetConsoleTextAttribute(hc, DEFAULT);
  style_printf(BRIGHT_WHITE, "POINTS ] \n");
}

unsigned short int get_shop() {
  unsigned short int option = 0;
  style_printf(
    BRIGHT_WHITE,
    "1 : More pokeballs \n2 : Styles (COMING SOON) \n3 : Return to menu \n");
  scanf("%hu", &option);
  return option;
};

unsigned short int get_ball_shop() {
  unsigned short int option = 0;
  style_printf(
    BRIGHT_WHITE,
    "1 : Poke Balls\t\t|| 20 points\n2 : Great Balls\t\t|| 100 points\n3 : Ultra Balls\t\t|| 1000 points\n4 : Master Balls\t|| 10000 points\n5 : Exit \n");
  scanf("%hu", &option);
  return option;
}

int get_showcase_choice(int showcase_index) {
  int option = 0;
  printf("ENTER A POKEMON NUMBER TO SHOWCASE : ");
  scanf("%d", &option);
  while (option >= showcase_index) {
    SetConsoleTextAttribute(hc, RED | FOREGROUND_INTENSITY);
    printf(":: ERROR CHOICE OUT OF RANGE RE-ENTER \n");
    SetConsoleTextAttribute(hc, DEFAULT);
    scanf("%d", &option);
  }

  return option;
};