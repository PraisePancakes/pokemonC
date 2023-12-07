#include "pokemon.h"
#include "gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void disp_pokemon(Pokemon *pokemon, unsigned short int index) {
  printf("\n POKEMON %d { NAME : %s , TYPE : %s } \n",
         index,
         pokemon->name,
         pokemon->type);
};

void shinify_pokemon(Pokemon *p_pokemon) {
  const unsigned short int SHINY_DENOMINATOR = 20;
  const unsigned short int SHINY_NUMERATOR = 1;
  unsigned short int random_shiny_factor = rand() % SHINY_DENOMINATOR;
  if (random_shiny_factor == SHINY_NUMERATOR) {
    p_pokemon->is_shiny = true;
  } else {
    p_pokemon->is_shiny = false;
  }
}

Pokemon *gen_rand_pokemon(Pokemon *p_pokemon, unsigned short int size) {
  srand(time(NULL));
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
  shinify_pokemon(p_pokemon + random_index);
  return p_pokemon + random_index;
}