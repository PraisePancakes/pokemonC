#ifndef BALL_H
#define BALL_H

typedef struct Ball {
  char *type;
  unsigned short int modifier;     // based on type 1.5 , 3 , 5 , 10
  unsigned short int catch_chance; // base * modifier
  unsigned short int points_to_buy;
} Ball;

typedef struct BallNode {
  Ball *data;
  struct BallNode *next;
} BallNode;

enum BallModifiers {
  POKEBALL_MOD = 1,
  GREATBALL_MOD = 3,
  ULTRABALL_MOD = 5,
  MASTERBALL_MOD = 10
};

enum BallPrices {
  POKEBALL_PRICE = 20,
  GREATBALL_PRICE = 100,
  ULTRABALL_PRICE = 1000,
  MASTERBALL_PRICE = 10000
};

Ball *create_pokeball(char *type,
                      unsigned short int modifier,
                      unsigned short int price); // ball.h

#endif