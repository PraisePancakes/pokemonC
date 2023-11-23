#include "ball.h"
#define BALL_BASE_VAL 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Ball *create_pokeball(char *type,
                      unsigned short int modifier,
                      unsigned short int price) {

  Ball *new_ball = malloc(sizeof(Ball));
  new_ball->type = malloc(strlen(type) + 1);

  if (new_ball == NULL || new_ball->type == NULL) {
    fprintf(stderr, "Failed mallocation for new_ball");
    free(new_ball->type);
    free(new_ball);
    exit(EXIT_FAILURE);
  }

  strcpy(new_ball->type, type);
  new_ball->catch_chance = BALL_BASE_VAL * modifier;
  new_ball->points_to_buy = price;
  return new_ball;
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