#include "file.h"
#include <stdio.h>
#include <stdlib.h>

void save_pokedex(FILE *file, PokeNode *head) {
  while (head != NULL) {
    fwrite(head->data, sizeof(Pokemon), 1, file);
    head = head->next;
  }
}

PokeNode *load_pokedex(FILE *file) {
  PokeNode *head = NULL;
  PokeNode *current = NULL;
  Pokemon *temp_pokemon = malloc(sizeof(Pokemon));

  while (fread(temp_pokemon, sizeof(Pokemon), 1, file) == 1) {
    PokeNode *new_node = malloc(sizeof(PokeNode));
    new_node->data = temp_pokemon;
    new_node->next = NULL;

    if (head == NULL) {
      head = new_node;
      current = head;
    } else {
      current->next = new_node;
      current = new_node;
    }

    // Allocate new memory for the next Pokemon
    temp_pokemon = malloc(sizeof(Pokemon));
  }

  free(temp_pokemon); // Free the last allocated Pokemon (if any)

  return head;
}

void save_ball_list(FILE *file, BallNode *head) {
  while (head != NULL) {
    // Write each Ball node to the file
    fwrite(head->data, sizeof(Ball), 1, file);
    head = head->next;
  }
}

BallNode *load_ball_list(FILE *file) {
  BallNode *head = NULL;
  BallNode *current = NULL;
  Ball *temp_ball = (Ball *)malloc(sizeof(Ball));

  while (fread(temp_ball, sizeof(Ball), 1, file) == 1) {
    BallNode *new_node = (BallNode *)malloc(sizeof(BallNode));
    new_node->data = temp_ball;
    new_node->next = NULL;

    if (head == NULL) {
      head = new_node;
      current = head;
    } else {
      current->next = new_node;
      current = new_node;
    }

    // Allocate new memory for the next Ball
    temp_ball = (Ball *)malloc(sizeof(Ball));
  }

  free(temp_ball); // Free the last allocated Ball (if any)

  return head;
}

void save_player(Player *player, const char *file_name) {
  FILE *file = fopen(file_name, "wb");
  if (file == NULL) {
    fprintf(stderr, "Error opening file for writing: %s\n", file_name);
    return;
  }

  fwrite(player, sizeof(Player), 1, file);

  save_pokedex(file, player->Phead);
  save_ball_list(file, player->Bhead);

  fclose(file);
}

Player *load_player(const char *file_name) {
  FILE *file = fopen(file_name, "rb");
  if (file == NULL) {
    fprintf(stderr, "Error opening file for reading: %s\n", file_name);
    return NULL;
  }

  Player *player = malloc(sizeof(Player));

  fread(player, sizeof(Player), 1, file);

  player->Phead = load_pokedex(file);
  player->Bhead = load_ball_list(file);

  fclose(file);

  return player;
}
