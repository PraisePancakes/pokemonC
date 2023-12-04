#ifndef POKEMON_H
#define POKEMON_H
#include <stdbool.h>

typedef struct Pokemon {
  char *name;
  char *type;
  bool is_legendary;
  unsigned short int catch_difficulty; // 10 - 100 , if ball catch_chance >=
                                       // catch_difficulty ? success : fail
} Pokemon;

typedef struct PokeNode {
  Pokemon *data;
  struct PokeNode *next;
} PokeNode;

enum MultiplierConstants {
  LEGENDARY = 10,
  NORMAL = 5,
  LEGENDARY_MIN = 7,
  LEGENDARY_MAX = 10,
  NORMAL_MIN = 1,
  NORMAL_MAX = 11
};

void disp_pokemon(Pokemon *pokemon, unsigned short int index); // pokemon.h
void _init_pokemon_list(Pokemon *p_pokemon);                   // pokemon.h
void _init_pokemon_catch_chance(Pokemon *p_pokemon);
Pokemon *gen_rand_pokemon(Pokemon *p_pokemon,
                          unsigned short int size); // pokemon.h

#endif