#include "pokemon.h"
#include "gui.h"
#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_POKEMONS 20

void disp_pokemon(Pokemon *pokemon, unsigned short int index) {
  printf("\n POKEMON %d { NAME : %s , TYPE : %s } \n",
         index,
         pokemon->name,
         pokemon->type);
};

void _init_pokemons_list(Pokemon *p_pokemons) {
  p_pokemons[0].name = "Pikachu";
  p_pokemons[0].type = "Electric";
  p_pokemons[0].is_legendary = false;

  p_pokemons[1].name = "Bulbasaur";
  p_pokemons[1].type = "Grass/Poison";
  p_pokemons[1].is_legendary = false;

  p_pokemons[2].name = "Charmander";
  p_pokemons[2].type = "Fire";
  p_pokemons[2].is_legendary = false;

  p_pokemons[3].name = "Squirtle";
  p_pokemons[3].type = "Water";
  p_pokemons[3].is_legendary = false;

  p_pokemons[4].name = "Jigglypuff";
  p_pokemons[4].type = "Normal/Fairy";
  p_pokemons[4].is_legendary = false;

  p_pokemons[5].name = "Mewtwo";
  p_pokemons[5].type = "Psychic";
  p_pokemons[5].is_legendary = true;

  p_pokemons[6].name = "Snorlax";
  p_pokemons[6].type = "Normal";
  p_pokemons[6].is_legendary = false;

  p_pokemons[7].name = "Eevee";
  p_pokemons[7].type = "Normal";
  p_pokemons[7].is_legendary = false;

  p_pokemons[8].name = "Gyarados";
  p_pokemons[8].type = "Water/Flying";
  p_pokemons[8].is_legendary = false;

  p_pokemons[9].name = "Dragonite";
  p_pokemons[9].type = "Dragon/Flying";
  p_pokemons[9].is_legendary = false;

  p_pokemons[10].name = "Machop";
  p_pokemons[10].type = "Fighting";
  p_pokemons[10].is_legendary = false;

  p_pokemons[11].name = "Alakazam";
  p_pokemons[11].type = "Psychic";
  p_pokemons[11].is_legendary = false;

  p_pokemons[12].name = "Geodude";
  p_pokemons[12].type = "Rock/Ground";
  p_pokemons[12].is_legendary = false;

  p_pokemons[13].name = "Moltres";
  p_pokemons[13].type = "Fire/Flying";
  p_pokemons[13].is_legendary = true;

  p_pokemons[14].name = "Gengar";
  p_pokemons[14].type = "Ghost/Poison";
  p_pokemons[14].is_legendary = false;

  p_pokemons[15].name = "Magikarp";
  p_pokemons[15].type = "Water";
  p_pokemons[15].is_legendary = false;

  p_pokemons[16].name = "Ditto";
  p_pokemons[16].type = "Normal";
  p_pokemons[16].is_legendary = false;

  p_pokemons[17].name = "Rayquaza";
  p_pokemons[17].type = "Dragon/Flying";
  p_pokemons[17].is_legendary = true;

  p_pokemons[18].name = "Psyduck";
  p_pokemons[18].type = "Water";
  p_pokemons[18].is_legendary = false;

  p_pokemons[19].name = "Clefairy";
  p_pokemons[19].type = "Fairy";
  p_pokemons[19].is_legendary = false;

  const unsigned short int LEGENDARY_CONST = 10;
  const unsigned short int NORMAL_CONST = 5;
  const unsigned short int LEGENDARY_MIN = 7;
  const unsigned short int LEGENDARY_MAX = 10;
  const unsigned short int NORMAL_MIN_RANGE = 1;
  const unsigned short int NORMAL_MAX_RANGE = 11;

  for (int i = 0; i < NUM_OF_POKEMONS; i++) {
    unsigned short int rand_mult;
    if (p_pokemons[i].is_legendary) {
      rand_mult = LEGENDARY_CONST *
                  (rand() % (LEGENDARY_MAX - LEGENDARY_MIN) + LEGENDARY_MIN);
      p_pokemons[i].catch_difficulty = rand_mult;
    } else if (!p_pokemons[i].is_legendary) {
      rand_mult =
        NORMAL_CONST *
        (rand() % (NORMAL_MAX_RANGE - NORMAL_MIN_RANGE) + NORMAL_MIN_RANGE);
      p_pokemons[i].catch_difficulty = rand_mult;
    }
  }
}

Pokemon *gen_rand_pokemon(Pokemon *p_pokemons, unsigned short int size) {
  unsigned short int random_index = rand() % size;
  while ((p_pokemons + random_index)->is_legendary) {
    const unsigned short int LEGENDARY_THRESHOLD = 100;
    unsigned short int max = 1000;
    unsigned short int curtail_randomizer = rand() % max;
    if (curtail_randomizer <= LEGENDARY_THRESHOLD) {
      return p_pokemons + random_index;
    } else {
      random_index = rand() % size;
    }
  }
  if ((p_pokemons + random_index)->is_legendary) {
    style_printf_encountered(YELLOW, (p_pokemons + random_index));
  } else {
    style_printf_encountered(LIGHT_AQUA, (p_pokemons + random_index));
  }
  return p_pokemons + random_index;
}