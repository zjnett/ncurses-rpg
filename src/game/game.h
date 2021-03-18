#ifndef GAME_H
#define GAME_H

#include "rpg.h"
#include "window.h"

int do_game_loop(window_info *wi);
int update_buffer(char *buffer, char *src, int *buffer_length);

#endif