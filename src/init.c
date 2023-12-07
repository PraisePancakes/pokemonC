#include "init.h"
#define NUM_OF_POKEMONS 39
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void _init_pokemon_list(Pokemon *p_pokemon) {
  p_pokemon[0].name = "Pikachu";
  p_pokemon[0].type = "Electric";
  p_pokemon[0].is_legendary = false;

  p_pokemon[1].name = "Bulbasaur";
  p_pokemon[1].type = "Grass/Poison";
  p_pokemon[1].is_legendary = false;

  p_pokemon[2].name = "Charmander";
  p_pokemon[2].type = "Fire";
  p_pokemon[2].is_legendary = false;

  p_pokemon[3].name = "Squirtle";
  p_pokemon[3].type = "Water";
  p_pokemon[3].is_legendary = false;

  p_pokemon[4].name = "Jigglypuff";
  p_pokemon[4].type = "Normal/Fairy";
  p_pokemon[4].is_legendary = false;

  p_pokemon[5].name = "Mewtwo";
  p_pokemon[5].type = "Psychic";
  p_pokemon[5].is_legendary = true;

  p_pokemon[6].name = "Snorlax";
  p_pokemon[6].type = "Normal";
  p_pokemon[6].is_legendary = false;

  p_pokemon[7].name = "Eevee";
  p_pokemon[7].type = "Normal";
  p_pokemon[7].is_legendary = false;

  p_pokemon[8].name = "Gyarados";
  p_pokemon[8].type = "Water/Flying";
  p_pokemon[8].is_legendary = false;

  p_pokemon[9].name = "Dragonite";
  p_pokemon[9].type = "Dragon/Flying";
  p_pokemon[9].is_legendary = false;

  p_pokemon[10].name = "Machop";
  p_pokemon[10].type = "Fighting";
  p_pokemon[10].is_legendary = false;

  p_pokemon[11].name = "Alakazam";
  p_pokemon[11].type = "Psychic";
  p_pokemon[11].is_legendary = false;

  p_pokemon[12].name = "Geodude";
  p_pokemon[12].type = "Rock/Ground";
  p_pokemon[12].is_legendary = false;

  p_pokemon[13].name = "Moltres";
  p_pokemon[13].type = "Fire/Flying";
  p_pokemon[13].is_legendary = true;

  p_pokemon[14].name = "Gengar";
  p_pokemon[14].type = "Ghost/Poison";
  p_pokemon[14].is_legendary = false;

  p_pokemon[15].name = "Magikarp";
  p_pokemon[15].type = "Water";
  p_pokemon[15].is_legendary = false;

  p_pokemon[16].name = "Ditto";
  p_pokemon[16].type = "Normal";
  p_pokemon[16].is_legendary = false;

  p_pokemon[17].name = "Rayquaza";
  p_pokemon[17].type = "Dragon/Flying";
  p_pokemon[17].is_legendary = true;

  p_pokemon[18].name = "Psyduck";
  p_pokemon[18].type = "Water";
  p_pokemon[18].is_legendary = false;

  p_pokemon[19].name = "Clefairy";
  p_pokemon[19].type = "Fairy";
  p_pokemon[19].is_legendary = false;

  //==================================================

  p_pokemon[20].name = "Absol";
  p_pokemon[20].type = "Dark";
  p_pokemon[20].is_legendary = false;

  p_pokemon[21].name = "Lugia";
  p_pokemon[21].type = "Psychic/Flying";
  p_pokemon[21].is_legendary = true;

  p_pokemon[22].name = "Dialga";
  p_pokemon[22].type = "Steel/Flying";
  p_pokemon[22].is_legendary = true;

  p_pokemon[23].name = "Zapdos";
  p_pokemon[23].type = "Electric/Flying";
  p_pokemon[23].is_legendary = true;

  p_pokemon[24].name = "Ho-Oh";
  p_pokemon[24].type = "Fire/Flying";
  p_pokemon[24].is_legendary = true;

  p_pokemon[25].name = "Suicune";
  p_pokemon[25].type = "Water";
  p_pokemon[25].is_legendary = true;

  p_pokemon[26].name = "Regigigas";
  p_pokemon[26].type = "Noraml";
  p_pokemon[26].is_legendary = true;

  p_pokemon[27].name = "Charizard";
  p_pokemon[27].type = "Fire/Flying";
  p_pokemon[27].is_legendary = false;

  p_pokemon[28].name = "Charmeleon";
  p_pokemon[28].type = "Fire";
  p_pokemon[28].is_legendary = false;

  p_pokemon[29].name = "Wartortle";
  p_pokemon[29].type = "Water";
  p_pokemon[29].is_legendary = false;

  p_pokemon[30].name = "Caterpie";
  p_pokemon[30].type = "Bug";
  p_pokemon[30].is_legendary = false;

  p_pokemon[31].name = "Metapod";
  p_pokemon[31].type = "Bug";
  p_pokemon[31].is_legendary = false;

  p_pokemon[32].name = "Butterfree";
  p_pokemon[32].type = "Bug/Flying";
  p_pokemon[32].is_legendary = false;

  p_pokemon[33].name = "Weedle";
  p_pokemon[33].type = "Bug/Poison";
  p_pokemon[33].is_legendary = false;

  p_pokemon[34].name = "Kakuna";
  p_pokemon[34].type = "Bug/Poison";
  p_pokemon[34].is_legendary = false;

  p_pokemon[35].name = "Beedrill";
  p_pokemon[35].type = "Bug/Poison";
  p_pokemon[35].is_legendary = false;

  p_pokemon[36].name = "Pidgey";
  p_pokemon[36].type = "Normal/Flying";
  p_pokemon[36].is_legendary = false;

  p_pokemon[37].name = "Pidgeotto";
  p_pokemon[37].type = "Normal/Flying";
  p_pokemon[37].is_legendary = false;

  p_pokemon[38].name = "Pidgeot";
  p_pokemon[38].type = "Normal/Flying";
  p_pokemon[38].is_legendary = false;
}

void _init_pokemon_catch_chance(Pokemon *p_pokemon) {
  srand(time(NULL));
  for (int i = 0; i < NUM_OF_POKEMONS; i++) {
    unsigned short int rand_mult;
    if (p_pokemon[i].is_legendary) {
      rand_mult =
        LEGENDARY * (rand() % (LEGENDARY_MAX - LEGENDARY_MIN) + LEGENDARY_MIN);
      p_pokemon[i].catch_difficulty = rand_mult;
    } else if (!p_pokemon[i].is_legendary) {
      rand_mult = NORMAL * (rand() % (NORMAL_MAX - NORMAL_MIN) + NORMAL_MIN);
      p_pokemon[i].catch_difficulty = rand_mult;
    }
  }
};

Player *_init_player() {
  Player *new_player = malloc(sizeof(Player));

  if (new_player == NULL) {
    fprintf(stderr, "ERROR :: MALLOC FAILED FOR NEW_PLAYER");
    free(new_player);
    exit(EXIT_FAILURE);
  }

  new_player->xp = 0;
  new_player->Bhead = NULL;
  new_player->Phead = NULL;
  new_player->showcase = malloc(4);
  new_player->showcase_type = malloc(4);
  new_player->points = 0;

  if (new_player->showcase == NULL) {
    fprintf(stderr, "ERROR :: MALLOC FAILED FOR NEW_PLAYER->SHOWCASE");
    free(new_player->showcase);
    exit(EXIT_FAILURE);
  }
  strcpy(new_player->showcase, "TBA");

  strcpy(new_player->showcase_type, "TBA");

  return new_player;
}

BallNode *_init_ball_llist() {
  BallNode *head = malloc(sizeof(BallNode));
  BallNode *first_node = malloc(sizeof(BallNode));
  BallNode *second_node = malloc(sizeof(BallNode));
  BallNode *third_node = malloc(sizeof(BallNode));

  if (head == NULL || first_node == NULL || second_node == NULL ||
      third_node == NULL) {
    fprintf(stderr, "ERROR :: MALLOC FAILED FOR _INIT_BALL_LLIST");
    free(head);
    free(first_node);
    free(second_node);
    free(third_node);
    exit(EXIT_FAILURE);
  }

  Ball *starter_pokeball =
    create_pokeball("pokeball", POKEBALL_MOD, POKEBALL_PRICE);
  Ball *starter_greatball =
    create_pokeball("greatball", GREATBALL_MOD, GREATBALL_PRICE);
  Ball *starter_ultraball =
    create_pokeball("ultraball", ULTRABALL_MOD, ULTRABALL_PRICE);
  Ball *starter_masterball =
    create_pokeball("masterball", MASTERBALL_MOD, MASTERBALL_PRICE);
  printf("MASTERBALL CATCH CHANCE : %d", starter_masterball->catch_chance);

  head->data = starter_pokeball;
  head->next = first_node;
  first_node->data = starter_greatball;
  first_node->next = second_node;
  second_node->data = starter_ultraball;
  second_node->next = third_node;
  third_node->data = starter_masterball;
  third_node->next = NULL;

  return head;
}