#ifndef GAME_H
#define GAME_H

#include "rpg.h"
#include "window.h"
#include "menu.h"

int do_game_loop(window_info *wi);
int update_buffer(char *buffer, char *src, int *buffer_length);
void exec_new_game(void);

extern enum game_mode mode;
extern menu_option menu_options[100];

#endif