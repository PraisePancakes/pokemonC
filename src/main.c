#include "ball.h"
#include "gui.h"
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
1 : save file, read file
2 : implement store
3 : implement Inventory and item count system ** IMPORTANT!!
*/

int main() {
  const char *filename = "PokeSave.bin";

  hc = GetStdHandle(STD_OUTPUT_HANDLE);
  Player *player = malloc(sizeof(Player));

  if (player == NULL) {
    fprintf(stderr, "ERROR :: MEM ALLOC FAILED FOR PLAYER \n");
    free(player);
    exit(EXIT_FAILURE);
  }

  player->showcase = NULL;
  Pokemon pokemons[NUM_OF_POKEMONS];
  Pokemon *p_pokemons = &pokemons[0];
  bool _has_init = false;

  char *version = "v0.0.0-unreleased";
  system("cls");

  welcome(version);

  player = get_player();
  player->Bhead = _init_ball_llist();
  style_printf(YELLOW, "\n =-=-= HERE ARE YOUR STARTING BALLS =-=-= \n");
  disp_inv_ball_list(player);

  player->Phead = NULL;

  style_printf(WHITE, "press any key to go to the menu...");
  getch();
  unsigned short int menu_option = 0;
  const unsigned short int MENU_EXIT = 4;

  while (menu_option != MENU_EXIT) {
    system("cls");
    fflush(stdin);

    menu_option = get_menu(player);
    switch (menu_option) {
      case 1:
        if (!_has_init) {
          _init_pokemons_list(p_pokemons);
          _has_init = true;
        }
        style_printf(LIGHT_PURPLE, "\n =-= ON ROUTE FOR CATCHING =-= \n");
        disp_walking();
        Pokemon *random_pokemon = gen_rand_pokemon(p_pokemons, NUM_OF_POKEMONS);
        if (player->Bhead == NULL) {
          style_printf(RED,
                       ":: YOU DO NOT HAVE ANY POKEBALLS, VISIT THE STORE TO "
                       "BUY MORE :: \n");
          break;
        }
        int catch_option = 0;
        printf("[1] catch [2] run\n");
        scanf("%d", &catch_option);
        switch (catch_option) {
          case 1:
            handle_catching(player, random_pokemon);
            getch();
            break;
          case 2:
            style_printf_fled(RED, random_pokemon);
            printf("press any key to go to the menu...");
            getch();
            break;
          default: printf("Invalid option try again : "); break;
        }
        getch();
        break;
      case 2:
        style_printf(YELLOW, "\n =-= SHOWCASE =-= \n");

        if (player->Phead == NULL) {
          style_printf(RED, ":: NO POKEMONS IN POKEDEX CURRENTLY :: \n");
        } else {
          int showcase_index = 1;
          disp_pokedex(player, &showcase_index);
          int showcase_choice = get_showcase_choice(showcase_index);
          add_to_showcase(player, showcase_choice);
        }

        getch();
        break;
      case 3:
        style_printf(LIGHT_YELLOW, "=-= ITEM SHOP =-= \n");
        const unsigned short int POINTS_TEXT_STYLE =
          player->points > 0 ? GREEN : RED;
        style_printf_points(POINTS_TEXT_STYLE, player);
        if (player->points < POKEBALL_PRICE) {
          style_printf(LIGHT_RED, "COME BACK WHEN YOU HAVE MORE POINTS!");
          getch();
          break;
        }
        unsigned short int shop_option = get_shop();
        switch (shop_option) {
          case 1:
            style_printf(LIGHT_YELLOW, "=-= BUY POKEBALLS =-= \n");
            style_printf_points(POINTS_TEXT_STYLE, player);
            if (player->points < POKEBALL_PRICE) {
              style_printf(LIGHT_RED, "COME BACK WHEN YOU HAVE MORE POINTS!");
              break;
            }
            style_printf(LIGHT_YELLOW,
                         "=-= SELECT WHICH BALL YOU WOULD LIKE TO BUY =-= \n");
            unsigned short int ball_buy_option = get_ball_shop();
            // buy_ball(Player* player , Ball* ball);
            switch (ball_buy_option) {
              case 1:
                style_printf(LIGHT_RED, "BUYING POKEBALL...");
                Ball *ball_item =
                  create_pokeball("pokeball", POKEBALL_MOD, POKEBALL_PRICE);
                buy_ball(player, ball_item);
                getch();
                break;

              case 2:
                style_printf(BLUE, "BUYING GREATBALL...");
                ball_item =
                  create_pokeball("greatball", GREATBALL_MOD, GREATBALL_PRICE);
                buy_ball(player, ball_item);
                getch();
                break;

              case 3:
                style_printf(LIGHT_YELLOW,
                             "BUYING ULTRABALL..."); // buy_ball();
                ball_item =
                  create_pokeball("ultraball", ULTRABALL_MOD, ULTRABALL_PRICE);
                buy_ball(player, ball_item);
                getch();
                break;

              case 4:
                style_printf(LIGHT_PURPLE,
                             "BUYING MASTERBALL..."); // buy_masterball();
                ball_item = create_pokeball(
                  "masterball", MASTERBALL_MOD, MASTERBALL_PRICE);
                buy_ball(player, ball_item);
              case 5:
                style_printf(PURPLE,
                             "EXITING SHOP... PRESS ANY KEY TO RETURN TO MENU");
                getch();
                break;
            }
            getch();
            break;
        }
        getch();
        break;
      case 4:
        free_pokedex(player);
        free_pokeballs(player);
        player->Phead = NULL;
        player->Bhead = NULL;
        free(player->showcase);
        free(player->username);

        free(player);
        printf("Thanks for playing!");

        break;
      default: {
        printf("Invalid option try again : ");
        getch();
      }
    }
  }

  return 0;
}
