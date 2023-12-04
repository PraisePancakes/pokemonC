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
