#include "player.h"
#include "gui.h"
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void disp_inv_ball_list(Player *player) {
  int ball_inv_amount = 1;
  int _iter = 1;
  BallNode *tmp = player->Bhead;

  while (tmp != NULL) {
    SetConsoleTextAttribute(hc, BRIGHT_WHITE | FOREGROUND_INTENSITY);
    printf("%d : %d x %s \n", _iter, ball_inv_amount, tmp->data->type);
    tmp = tmp->next;
    _iter++;
  }
  SetConsoleTextAttribute(hc, DEFAULT);
}

void disp_pokedex(Player *player, int *showcase_index) {
  style_printf(YELLOW, "[ CHOOSE A POKEMON ] \n");
  PokeNode *tmp = player->Phead;
  while (tmp != NULL) {
    disp_pokemon(tmp->data, *showcase_index);
    tmp = tmp->next;
    *showcase_index = *showcase_index + 1;
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

Player *get_player() {
  srand(time(NULL));
  Player *new_player = _init_player();
  new_player->Bhead = _init_ball_llist();

  char input[INPUT_BUFFER];
  style_printf(YELLOW, "\n\n\n\n What is your username : \n");
  char *p_input = fgets(input, INPUT_BUFFER, stdin);
  strtok(p_input, "\n");
  new_player->username = malloc(strlen(p_input) + 1);
  if (new_player->username == NULL) {
    fprintf(stderr, "ERROR :: MALLOC FAILED FOR NEW_PLAYER->USERNAME");
    free(new_player->username);
    exit(EXIT_FAILURE);
  }
  strcpy(new_player->username, p_input);

  char *uuid = gen_player_uuid();

  strcpy(new_player->id, uuid);
  SetConsoleTextAttribute(hc, BLUE | FOREGROUND_INTENSITY);
  printf("USER : %s \n", new_player->username);
  printf("YOUR UUID : %s \n", new_player->id);
  printf("XP : %hu \n", new_player->xp);
  printf("POINTS : %hu ", new_player->points);
  SetConsoleTextAttribute(hc, DEFAULT);
  getch();

  return new_player;
}

char *gen_player_uuid() {
  char *uuid = malloc(9);
  const unsigned short int MIN_ASCII_NUMBER = 48;
  const unsigned short int MAX_ASCII_NUMBER = 57;
  const unsigned short int MIN_ASCII_LLETTER = 97;
  const unsigned short int MAX_ASCII_LLETTER = 122;

  for (int i = 0; i < 8; i++) {
    int rand_code;
    if (i % 2 == 0) {
      rand_code =
        rand() % (MAX_ASCII_NUMBER - MIN_ASCII_NUMBER) + MIN_ASCII_NUMBER;
    } else {
      rand_code =
        rand() % (MAX_ASCII_LLETTER - MIN_ASCII_LLETTER) + MIN_ASCII_LLETTER;
    }
    uuid[i] = (char)rand_code;
  }

  uuid[8] = '\0';

  return uuid;
}

Ball *choose_ball(Player *player, int *ball_option) {

  disp_inv_ball_list(player);
  int option = 0;
  scanf("%d", &option);

  BallNode *curr_ball = player->Bhead;
  int _iter = 1;
  while (_iter != option) {
    curr_ball = curr_ball->next;
    _iter++;
  }

  *ball_option = option;
  system("cls");
  style_printf(LIGHT_AQUA, "** You chose a ");
  if (strcmp(curr_ball->data->type, "pokeball") == 0) {
    SetConsoleTextAttribute(hc, LIGHT_RED);
    printf("%s", curr_ball->data->type);
    SetConsoleTextAttribute(hc, DEFAULT);
  } else if (strcmp(curr_ball->data->type, "greatball") == 0) {
    SetConsoleTextAttribute(hc, BLUE);
    printf("%s", curr_ball->data->type);
    SetConsoleTextAttribute(hc, DEFAULT);
  } else if (strcmp(curr_ball->data->type, "ultraball") == 0) {
    SetConsoleTextAttribute(hc, LIGHT_YELLOW);
    printf("%s", curr_ball->data->type);
    SetConsoleTextAttribute(hc, DEFAULT);
  } else if (strcmp(curr_ball->data->type, "masterball") == 0) {
    SetConsoleTextAttribute(hc, PURPLE);
    printf("%s", curr_ball->data->type);
    SetConsoleTextAttribute(hc, DEFAULT);
  };

  SetConsoleTextAttribute(hc, LIGHT_AQUA);
  printf(" with a catch chance of ");
  if (curr_ball->data->catch_chance == 10) {
    SetConsoleTextAttribute(hc, LIGHT_RED);
    printf("%hu", curr_ball->data->catch_chance);
    SetConsoleTextAttribute(hc, DEFAULT);
  } else if (curr_ball->data->catch_chance == 30) {
    SetConsoleTextAttribute(hc, BLUE);
    printf("%hu", curr_ball->data->catch_chance);
    SetConsoleTextAttribute(hc, DEFAULT);
  } else if (curr_ball->data->catch_chance == 50) {
    SetConsoleTextAttribute(hc, LIGHT_YELLOW);
    printf("%hu", curr_ball->data->catch_chance);
    SetConsoleTextAttribute(hc, DEFAULT);
  } else if (curr_ball->data->catch_chance == 100) {
    SetConsoleTextAttribute(hc, PURPLE);
    printf("%hu", curr_ball->data->catch_chance);
    SetConsoleTextAttribute(hc, DEFAULT);
  };

  SetConsoleTextAttribute(hc, LIGHT_AQUA);
  printf(" ** \n");
  SetConsoleTextAttribute(hc, DEFAULT);

  return curr_ball->data;
}

PokeNode *add_to_pokedex(Pokemon *pokemon, PokeNode *head) {
  PokeNode *new_node = malloc(sizeof(PokeNode));
  new_node->data = pokemon;
  new_node->next = NULL;

  if (head == NULL) {
    head = new_node;
  } else {
    PokeNode *tmp = malloc(sizeof(PokeNode));
    tmp = head;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = new_node;
  }
  return head;
}

void add_to_showcase(Player *player, int showcase_option) {
  int _iter = 1;

  PokeNode *tmp = player->Phead;
  printf("SHOWCASE OPT: %d", showcase_option);
  while (_iter != showcase_option) {
    tmp = tmp->next;
    _iter++;
  }

  free(player->showcase);
  player->showcase = strdup(tmp->data->name);
  if (player->showcase == NULL) {
    fprintf(stderr, "Memory allocation failed for showcase");
    exit(EXIT_FAILURE);
  }

  free(player->showcase_type);
  player->showcase_type = strdup(tmp->data->type);
  if (player->showcase_type == NULL) {
    fprintf(stderr, "Memory allocation failed for showcase type");
    exit(EXIT_FAILURE);
  }
}

BallNode *remove_ball(Player *player, int ball_option) {
  BallNode *curr = player->Bhead;
  BallNode *prev = player->Bhead;

  if (ball_option != 1) {
    int _iter = 1;
    while (_iter != ball_option - 1) {
      prev = prev->next;
      _iter++;
    }

    _iter = 1;
    while (_iter != ball_option) {
      curr = curr->next;
      _iter++;
    }

    prev->next = curr->next;
    curr->next = NULL;
    free(curr);
  } else if (ball_option == 1) {
    curr = curr->next;
    prev->next = NULL;
    free(prev);
    player->Bhead = curr;
  }

  return player->Bhead;
}

void throw_ball(Ball *chosen_ball, Pokemon *random_pokemon, Player *player) {
  if (chosen_ball->catch_chance >= random_pokemon->catch_difficulty) {
    player->Phead = add_to_pokedex(random_pokemon, player->Phead);
    unsigned short int previous_xp = player->xp;
    unsigned short int previous_points = player->points;
    if (player->xp == 0) {
      player->xp += random_pokemon->catch_difficulty + player->xp;
      player->points += random_pokemon->catch_difficulty + player->points;
    } else {
      player->xp += random_pokemon->catch_difficulty * floor(player->xp / 2);
      player->points += random_pokemon->catch_difficulty + player->points + 50;
    }

    SetConsoleTextAttribute(hc, LIGHT_AQUA | FOREGROUND_INTENSITY);
    printf(" ** YOU CAUGHT %s ** POKEMON { NAME : %s , TYPE : %s } HAS BEEN "
           "ADDED TO YOUR POKEDEX \n ",
           random_pokemon->name,
           random_pokemon->name,
           random_pokemon->type);
    SetConsoleTextAttribute(hc, DEFAULT);

    SetConsoleTextAttribute(hc, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("YOU GAINED %hu XP and %hu points!",
           abs(player->xp - previous_xp),
           abs(player->points - previous_points));
    SetConsoleTextAttribute(hc, DEFAULT);
  } else {
    printf("~~ MISSED ~~");
    // re throw or pokemon flees
  }
}

void buy_ball(Player *player, Ball *ball) {
  BallNode *new_ball = malloc(sizeof(BallNode));

  new_ball->data = ball;
  new_ball->next = NULL;

  if (player->Bhead == NULL) {
    player->Bhead = new_ball;
  } else {
    BallNode *tmp = malloc(sizeof(BallNode));
    tmp = player->Bhead;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = new_ball;
  }
  player->points = player->points - ball->points_to_buy;
};

void free_pokedex(Player *player) {
  PokeNode *tmp = player->Phead;
  while (tmp != NULL) {
    free(tmp->data->name);
    free(tmp->data->type);
    tmp = tmp->next;
  }
}

void free_pokeballs(Player *player) {
  BallNode *tmp = player->Bhead;
  while (tmp != NULL) {
    free(tmp->data->type);
    tmp = tmp->next;
  }
}

void handle_catching(Player *player, Pokemon *random_pokemon) {
  system("cls");
  style_printf(LIGHT_YELLOW, "\n =-= CHOOSE A BALL TO USE =-= \n");
  int ball_option = 0;
  Ball *chosen_ball = choose_ball(player, &ball_option);

  int action = 0;
  style_printf(LIGHT_GREEN, "[1] throw ball ");
  style_printf(LIGHT_YELLOW, "[2] change ball ");
  style_printf(LIGHT_RED, "[3] run \n");
  scanf("%d", &action);
  while (action == 2) {
    system("cls");
    style_printf(LIGHT_YELLOW, "\n =-= CHOOSE A BALL TO USE =-= \n");
    chosen_ball = choose_ball(player, &ball_option);
    style_printf(LIGHT_GREEN, "[1] throw ball ");
    style_printf(LIGHT_YELLOW, "[2] change ball ");
    style_printf(LIGHT_RED, "[3] run \n");
    scanf("%d", &action);
  }

  if (action == 1) {
    throw_ball(chosen_ball, random_pokemon, player);
    player->Bhead = remove_ball(player, ball_option);
  } else if (action == 3) {
    style_printf_fled(RED, random_pokemon);
    style_printf(BRIGHT_WHITE, "press any key to go to the menu...");
  }
}
