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

void disp_pokemon(Pokemon *pokemon, unsigned short int index); // pokemon.h
void _init_pokemons_list(Pokemon *p_pokemons);                 // pokemon.h
Pokemon *gen_rand_pokemon(Pokemon *p_pokemons,
                          unsigned short int size); // pokemon.h

#endif