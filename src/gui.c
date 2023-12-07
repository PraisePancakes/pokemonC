#include "gui.h"
#include <conio.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void style_printf(const char *format, WORD text_color, ...) {
  SetConsoleTextAttribute(hc, text_color | FOREGROUND_INTENSITY);

  va_list args;
  va_start(args, text_color);
  vprintf(format, args);
  va_end(args);

  SetConsoleTextAttribute(hc, DEFAULT);
}

void display_ball_actions() {
  style_printf("[1] throw ball ", LIGHT_GREEN);
  style_printf("[2] change ball ", LIGHT_YELLOW);
  style_printf("[3] run \n", LIGHT_RED);
}

void display_styled_ball_type(Ball *ball) {
  if (strcmp(ball->type, "pokeball") == 0) {
    style_printf("%s", LIGHT_RED, ball->type);
  } else if (strcmp(ball->type, "greatball") == 0) {
    style_printf("%s", BLUE, ball->type);
  } else if (strcmp(ball->type, "ultraball") == 0) {
    style_printf("%s", LIGHT_YELLOW, ball->type);
  } else if (strcmp(ball->type, "masterball") == 0) {
    style_printf("%s", PURPLE, ball->type);
  };
};

void display_styled_ball_catch_chance(Ball *ball) {
  if (ball->catch_chance == 10) {
    style_printf("%hu", LIGHT_RED, ball->catch_chance);
  } else if (ball->catch_chance == 30) {
    style_printf("%hu", BLUE, ball->catch_chance);
  } else if (ball->catch_chance == 50) {
    style_printf("%hu", LIGHT_YELLOW, ball->catch_chance);
  } else if (ball->catch_chance == 100) {
    style_printf("%hu", PURPLE, ball->catch_chance);
  };
};

void display_styled_ball_info(Ball *ball) {
  style_printf("** You chose a ", LIGHT_AQUA);
  display_styled_ball_type(ball);
  style_printf(" with a catch chance of ", LIGHT_AQUA);
  display_styled_ball_catch_chance(ball);
  style_printf(" ** \n", LIGHT_AQUA);
}

void welcome(char *version) {
  style_printf(
    "\n =-=-=-= WELCOME TO POKEMON C %s =-=-=-= \n", YELLOW, version);
  style_printf(
    "Pokemon C is a pokemon simulator\n[] catch pokemon\n[] showcase your pokemons\npress any key to advance...",
    WHITE);
  getch();
}

void display_encountered(Pokemon *random_pokemon) {
  if (random_pokemon->is_legendary) {
    style_printf("** YOU ENCOUNTERED %s ** \n", YELLOW, random_pokemon->name);
  } else {
    if (random_pokemon->is_shiny) {
      style_printf("** YOU ENCOUNTERED SHINY %s ** \n",
                   LIGHT_YELLOW,
                   random_pokemon->name);
    } else {
      style_printf(
        "** YOU ENCOUNTERED %s ** \n", LIGHT_AQUA, random_pokemon->name);
    }
  }
};

void disp_walking() {
  const unsigned short int MAX_SLEEP_INTERVAL = 4;
  unsigned short int random_sleep_interval = rand() % MAX_SLEEP_INTERVAL;
  bool _done_walking = false;
  while (!_done_walking) {
    sleep(1);
    style_printf("Walking... \n", BRIGHT_WHITE);
    sleep(1);
    style_printf("Walking... \n", BRIGHT_WHITE);
    sleep(MAX_SLEEP_INTERVAL);
    _done_walking = true;
  }
}

void display_player_stats(Player *player) {
  style_printf(
    "USER { username : %s, id : %s, xp : %hu, points : %hu, showcase : [%s :: %s] "
    "}\n ",
    BLUE,
    player->username,
    player->id,
    player->xp,
    player->points,
    player->showcase,
    player->showcase_type);
}

unsigned short int get_menu(Player *player) {
  unsigned short int option = 0;
  style_printf("\n=-=-= POKEMON C =-=-=\n", YELLOW);
  style_printf("1 : CATCH \n2 : SHOWCASE \n3 : ITEM SHOP \n4 : EXIT \n",
               BRIGHT_WHITE);
  scanf("%hu", &option);
  return option;
}

unsigned short int get_shop() {
  unsigned short int option = 0;
  style_printf(
    "1 : More pokeballs \n2 : Styles (COMING SOON) \n3 : Return to menu \n",
    BRIGHT_WHITE);
  scanf("%hu", &option);
  return option;
};

unsigned short int get_ball_shop() {
  unsigned short int option = 0;
  style_printf(
    "1 : Poke Balls\t\t|| 20 points\n2 : Great Balls\t\t|| 100 points\n3 : Ultra Balls\t\t|| 1000 points\n4 : Master Balls\t|| 10000 points\n5 : Exit \n",
    BRIGHT_WHITE);
  scanf("%hu", &option);
  return option;
}

int get_showcase_choice(int showcase_index) {
  int option = 0;
  style_printf("ENTER A POKEMON NUMBER TO SHOWCASE : ", BRIGHT_WHITE);
  scanf("%d", &option);
  while (option >= showcase_index) {
    style_printf(":: ERROR CHOICE OUT OF RANGE RE-ENTER \n", RED);
    scanf("%d", &option);
  }

  return option;
};