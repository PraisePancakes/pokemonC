#include "pokemon.h"
#include "gui.h"
#include <stdio.h>
#include <stdlib.h>

void disp_pokemon(Pokemon *pokemon, unsigned short int index) {
  printf("\n POKEMON %d { NAME : %s , TYPE : %s } \n",
         index,
         pokemon->name,
         pokemon->type);
};

Pokemon *gen_rand_pokemon(Pokemon *p_pokemon, unsigned short int size) {
  unsigned short int random_index = rand() % size;
  while ((p_pokemon + random_index)->is_legendary) {
    const unsigned short int LEGENDARY_THRESHOLD = 100;
    unsigned short int max = 1000;
    unsigned short int curtail_randomizer = rand() % max;
    if (curtail_randomizer <= LEGENDARY_THRESHOLD) {
      return p_pokemon + random_index;
    } else {
      random_index = rand() % size;
    }
  }
  return p_pokemon + random_index;
}