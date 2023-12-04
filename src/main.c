#include "ball.h"
#include "file.h"
#include "gui.h"
#include "init.h"
#include "player.h"
#include "pokemon.h"
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

#define NUM_OF_POKEMONS 20
/*
===== TO DO ====
1 : gui style optional arguments  e.g.. style_printf(optional->struct, WORD
color, char* text); 2 : implement store 3 : implement Inventory and item count
system ** IMPORTANT!! 4 : refactor
*/

int main() {
  const char *player_filename = ".././save/PlayerSave.bin";
  const char *pokedex_filename = ".././save/DexSave.bin";
  const char *pokeballs_filename = ".././save/BallSave.bin";

  Pokemon pokemons[NUM_OF_POKEMONS];
  Pokemon *p_pokemons = &pokemons[0];
  _init_pokemon_list(p_pokemons);
  _init_pokemon_catch_chance(p_pokemons);

  hc = GetStdHandle(STD_OUTPUT_HANDLE);
  system("cls");
  char *version = "v0.0.1-alpha";
  welcome(version);
  Player *player = load_player(player_filename);
  bool _returning_player = false;
  if (player == NULL) {
    player = _init_player();
    player->Bhead = _init_ball_llist();
    get_player(player);
    style_printf("\n =-=-= HERE ARE YOUR STARTING BALLS =-=-= \n", YELLOW);
    disp_inv_ball_list(player);
    getch();
  } else {
    _returning_player = true;
    player->Bhead = load_pokeballs(pokeballs_filename);
    player->Phead = load_pokedex(pokedex_filename);
  }

  system("cls");
  if (_returning_player) {
    style_printf("** WELCOME BACK %s **", LIGHT_AQUA, player->username);
  }
  style_printf("\npress any key to go to the menu...", WHITE);
  getch();
  unsigned short int menu_option = 0;
  const unsigned short int MENU_EXIT = 4;

  while (menu_option != MENU_EXIT) {
    system("cls");
    fflush(stdin);

    display_player_stats(player);
    menu_option = get_menu(player);

    switch (menu_option) {
      case 1:
        system("cls");
        style_printf("\n =-= ON ROUTE FOR CATCHING =-= \n", LIGHT_PURPLE);
        disp_walking();
        Pokemon *random_pokemon = gen_rand_pokemon(p_pokemons, NUM_OF_POKEMONS);
        display_encountered(random_pokemon);
        if (player->Bhead == NULL) {
          style_printf(
            ":: YOU DO NOT HAVE ANY POKEBALLS, VISIT THE STORE TO BUY MORE :: \n",
            RED);
          break;
        }
        int catch_option = 0;
        style_printf("[1] catch ", LIGHT_GREEN);
        style_printf("[2] run\n", LIGHT_RED);
        scanf("%d", &catch_option);
        switch (catch_option) {
          case 1:
            handle_catching(player, random_pokemon);
            getch();
            break;
          case 2:
            style_printf(
              "** YOU RAN AWAY :: %s FLED ** \n", RED, random_pokemon->name);
            style_printf("press any key to go to the menu...", BRIGHT_WHITE);
            getch();
            break;
          default:
            style_printf(":: Invalid option try again :: ", LIGHT_RED);
            break;
        }
        getch();
        break;
      case 2:
        style_printf("\n =-= SHOWCASE =-= \n", YELLOW);

        if (player->Phead == NULL) {
          style_printf(":: NO POKEMONS IN POKEDEX CURRENTLY :: \n", RED);
        } else {
          int showcase_index = 1;
          disp_pokedex(player, &showcase_index);
          int showcase_choice = get_showcase_choice(showcase_index);
          add_to_showcase(player, showcase_choice);
        }

        getch();
        break;
      case 3:
        style_printf("=-= ITEM SHOP =-= \n", LIGHT_YELLOW);
        const unsigned short int POINTS_TEXT_STYLE =
          player->points > 0 ? GREEN : RED;
        style_printf(
          "[YOU HAVE %hu POINTS]", POINTS_TEXT_STYLE, player->points);
        if (player->points < POKEBALL_PRICE) {
          style_printf("COME BACK WHEN YOU HAVE MORE POINTS!", LIGHT_RED);
          getch();
          break;
        }
        unsigned short int shop_option = get_shop();
        switch (shop_option) {
          case 1:
            style_printf("=-= BUY POKEBALLS =-= \n", LIGHT_YELLOW);
            style_printf(
              "[YOU HAVE %hu POINTS]", POINTS_TEXT_STYLE, player->points);
            if (player->points < POKEBALL_PRICE) {
              style_printf("COME BACK WHEN YOU HAVE MORE POINTS!", LIGHT_RED);
              break;
            }
            style_printf("=-= SELECT WHICH BALL YOU WOULD LIKE TO BUY =-= \n",
                         LIGHT_YELLOW);
            unsigned short int ball_buy_option = get_ball_shop();
            // buy_ball(Player* player , Ball* ball);
            switch (ball_buy_option) {
              case 1:
                style_printf("BUYING POKEBALL...", LIGHT_RED);
                Ball *ball_item =
                  create_pokeball("pokeball", POKEBALL_MOD, POKEBALL_PRICE);
                buy_ball(player, ball_item);
                getch();
                break;

              case 2:
                style_printf("BUYING GREATBALL...", BLUE);
                ball_item =
                  create_pokeball("greatball", GREATBALL_MOD, GREATBALL_PRICE);
                buy_ball(player, ball_item);
                getch();
                break;

              case 3:
                style_printf("BUYING ULTRABALL...",
                             LIGHT_YELLOW); // buy_ball();
                ball_item =
                  create_pokeball("ultraball", ULTRABALL_MOD, ULTRABALL_PRICE);
                buy_ball(player, ball_item);
                getch();
                break;

              case 4:
                style_printf("BUYING MASTERBALL...",
                             LIGHT_PURPLE); // buy_masterball();
                ball_item = create_pokeball(
                  "masterball", MASTERBALL_MOD, MASTERBALL_PRICE);
                buy_ball(player, ball_item);
              case 5:
                style_printf("EXITING SHOP... PRESS ANY KEY TO RETURN TO MENU",
                             PURPLE);
                getch();
                break;
            }
            getch();
            break;
        }
        getch();
        break;
      case 4:

        save_player(player, player_filename);
        save_pokedex(player, pokedex_filename);
        save_pokeballs(player, pokeballs_filename);

        free_pokedex(player);
        free_pokeballs(player);
        player->Phead = NULL;
        player->Bhead = NULL;
        free(player->showcase);
        free(player->username);

        free(player);
        style_printf(">:> THANKS FOR PLAYING <:<", LIGHT_AQUA);

        break;
      default: {
        style_printf(":: Invalid option try again :: ", LIGHT_RED);
        getch();
      }
    }
  }

  return 0;
}
