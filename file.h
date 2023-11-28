#ifndef FILE_H
#define FILE_H
#include "player.h"

void save_player(Player *player, const char *file_name);

Player *load_player(const char *filename);
#endif