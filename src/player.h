#ifndef PLAYER_H
#define PLAYER_H
#define INPUT_BUFFER 256
#include "ball.h"
#include "pokemon.h"

typedef struct Player {
  BallNode *Bhead; // [ball1 -> ball2 -> NULL]
  PokeNode *Phead; // linked list of the pokemons the player has
  char *showcase;
  char *showcase_type;
  char *username;
  char id[9];
  unsigned short int xp;
  unsigned short int points;
} Player;

void disp_inv_ball_list(Player *player);
void disp_pokedex(Player *player, int *showcase_index);     // player.h
Player *_init_player();                                     // player.h
Player *get_player();                                       // player.h
char *gen_player_uuid();                                    // player.h
Ball *choose_ball(Player *player, int *ball_option);        // player.h
PokeNode *add_to_pokedex(Pokemon *pokemon, PokeNode *head); // player.h
void add_to_showcase(Player *player, int showcase_option);  // player.h
BallNode *remove_ball(Player *player, int ball_option);     // player.h
void throw_ball(Ball *chosen_ball,
                Pokemon *random_pokemon,
                Player *player);           // player.h
void buy_ball(Player *player, Ball *ball); // player.h
void free_pokedex(Player *player);         // player.h
void free_pokeballs(Player *player);       // player.h

//[ACTIONS HANDLERS]
void handle_catching(Player *player, Pokemon *random_pokemon); // player.h

#endif