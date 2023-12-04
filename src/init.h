#ifndef INIT_H
#define INIT_H
#include "ball.h"
#include "player.h"
#include "pokemon.h"

void _init_pokemon_list(Pokemon *p_pokemon);
void _init_pokemon_catch_chance(Pokemon *p_pokemon);
Player *_init_player();
BallNode *_init_ball_llist();

#endif