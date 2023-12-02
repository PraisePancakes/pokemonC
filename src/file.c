#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_pokedex(Player *player, const char *pokedex_filename) {
  FILE *file = fopen(pokedex_filename, "wb");
  if (file == NULL) {
    fclose(file);
    return;
  }
  if (player->Phead != NULL) {
    int pokedex_list_length = 0;
    PokeNode *temp_poke = player->Phead;
    while (temp_poke != NULL) {
      pokedex_list_length++;
      temp_poke = temp_poke->next;
    }
    fwrite(&pokedex_list_length, sizeof(int), 1, file);
    temp_poke = player->Phead;
    while (temp_poke != NULL) {
      size_t len = strlen(temp_poke->data->name);
      fwrite(&len, sizeof(size_t), 1, file);
      fwrite(temp_poke->data, sizeof(Pokemon) - sizeof(char *), 1, file);
      fwrite(temp_poke->data->name, len, 1, file);
      temp_poke = temp_poke->next;
    }

    fclose(file);
  } else {
    fclose(file);
    return;
  }
}

void save_pokeballs(Player *player, const char *pokeballs_filename) {
  FILE *file = fopen(pokeballs_filename, "wb");
  if (file == NULL) {
    perror("Error opening file for writing");
    return;
  }

  int ball_list_length = 0;
  BallNode *temp_ball = player->Bhead;
  while (temp_ball != NULL) {
    ball_list_length++;
    temp_ball = temp_ball->next;
  }

  fwrite(&ball_list_length, sizeof(int), 1, file);

  temp_ball = player->Bhead;
  while (temp_ball != NULL) {
    size_t len = strlen(temp_ball->data->type);
    fwrite(&len, sizeof(size_t), 1, file);
    fwrite(temp_ball->data, sizeof(Ball) - sizeof(char *), 1, file);
    fwrite(temp_ball->data->type, len, 1, file);

    temp_ball = temp_ball->next;
  }

  fclose(file);
}

PokeNode *load_pokedex(const char *pokedex_filename) {
  FILE *file = fopen(pokedex_filename, "rb");
  if (file == NULL) {
    fprintf(stderr, "Error opening file for pokedex read");
    return NULL;
  }

  int poke_list_length;
  fread(&poke_list_length, sizeof(int), 1, file);

  PokeNode *head = NULL;
  PokeNode *current = NULL;
  if (poke_list_length != 0) {
    while (poke_list_length > 0) {
      size_t name_len;
      if (fread(&name_len, sizeof(size_t), 1, file) != 1) {
        break;
      }
      Pokemon *newPokemon = malloc(sizeof(Pokemon));
      if (fread(newPokemon, sizeof(Pokemon) - sizeof(char *), 1, file) != 1) {
        free(newPokemon);
        break;
      }
      newPokemon->name = malloc(name_len + 1);
      if (fread(newPokemon->name, name_len, 1, file) != 1) {
        free(newPokemon->name);
        free(newPokemon);
        break;
      }
      newPokemon->name[name_len] = '\0';
      PokeNode *newNode = malloc(sizeof(PokeNode));
      newNode->data = newPokemon;
      newNode->next = NULL;

      if (head == NULL) {
        head = newNode;
        current = head;
      } else {
        current->next = newNode;
        current = newNode;
      }

      poke_list_length--;
    }
  }
  return head;
}

BallNode *load_pokeballs(const char *pokeballs_filename) {
  FILE *file = fopen(pokeballs_filename, "rb");
  if (file == NULL) {
    fprintf(stderr, "Error opening file for pokeballs read");
    return NULL;
  }

  int ball_list_length;
  fread(&ball_list_length, sizeof(int), 1, file);

  BallNode *head = NULL;
  BallNode *current = NULL;
  if (ball_list_length != 0) {
    while (ball_list_length > 0) {

      size_t type_len;
      if (fread(&type_len, sizeof(size_t), 1, file) != 1) {
        break;
      }

      // Read a Ball structure from the file
      Ball *newBall = malloc(sizeof(Ball));
      if (fread(newBall, sizeof(Ball) - sizeof(char *), 1, file) != 1) {
        free(newBall);
        break;
      }

      newBall->type = malloc(type_len + 1);
      if (fread(newBall->type, type_len, 1, file) != 1) {
        free(newBall->type);
        free(newBall);
        break;
      }
      newBall->type[type_len] = '\0';

      BallNode *newNode = malloc(sizeof(BallNode));
      newNode->data = newBall;
      newNode->next = NULL;

      if (head == NULL) {
        head = newNode;
        current = head;
      } else {
        current->next = newNode;
        current = newNode;
      }

      ball_list_length--;
    }
  }

  fclose(file);
  return head;
}

void save_player(Player *player, const char *player_filename) {
  FILE *file;
  file = fopen(player_filename, "wb");
  if (file == NULL) {
    fclose(file);
    return;
  }
  fwrite(player, sizeof(Player), 1, file);

  size_t name_length = strlen(player->username) + 1;
  fwrite(&name_length, sizeof(size_t), 1, file);
  fwrite(player->username, sizeof(char), name_length, file);

  size_t showcase_length = strlen(player->showcase) + 1;
  fwrite(&showcase_length, sizeof(size_t), 1, file);
  fwrite(player->showcase, sizeof(char), showcase_length, file);

  size_t showcase_type_length = strlen(player->showcase_type) + 1;
  fwrite(&showcase_type_length, sizeof(size_t), 1, file);
  fwrite(player->showcase_type, sizeof(char), showcase_type_length, file);

  size_t id_length = strlen(player->id) + 1;
  fwrite(&id_length, sizeof(size_t), 1, file);
  fwrite(player->id, sizeof(char), id_length, file);

  fclose(file);
}

Player *load_player(const char *player_filename) {
  Player *loaded_player = malloc(sizeof(Player));
  FILE *file;
  file = fopen(player_filename, "rb");
  if (file == NULL || loaded_player == NULL) {
    if (loaded_player != NULL) {
      free(loaded_player);
    }
    return NULL;
  }

  fread(loaded_player, sizeof(Player), 1, file);

  size_t name_length;
  fread(&name_length, sizeof(size_t), 1, file);
  loaded_player->username = malloc(name_length);
  fread(loaded_player->username, sizeof(char), name_length, file);

  size_t showcase_length;
  fread(&showcase_length, sizeof(size_t), 1, file);
  loaded_player->showcase = malloc(showcase_length);
  fread(loaded_player->showcase, sizeof(char), showcase_length, file);

  size_t showcase_type_length;
  fread(&showcase_type_length, sizeof(size_t), 1, file);
  loaded_player->showcase_type = malloc(showcase_type_length);
  fread(loaded_player->showcase_type, sizeof(char), showcase_type_length, file);

  size_t id_length;
  fread(&id_length, sizeof(size_t), 1, file);
  fread(loaded_player->id, sizeof(char), id_length, file);

  fclose(file);
  return loaded_player;
}
