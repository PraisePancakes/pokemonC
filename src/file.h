#ifndef FILE_H
#define FILE_H
#include "player.h"

void save_player(Player *player, const char *player_filename);
Player *load_player(const char *player_filename);

void save_pokedex(Player *player, const char *pokedex_filename);
void save_pokeballs(Player *player, const char *pokeballs_filename);
PokeNode *load_pokedex(const char *pokedex_filename);
BallNode *load_pokeballs(const char *pokeballs_filename);

#endif