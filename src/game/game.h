#ifndef GAME_H
#define GAME_H

#include "rpg.h"
#include "window.h"
#include "menu.h"
#include "character.h"

int do_game_loop(window_info *wi);
void change_mode(game_mode m);
int update_buffer(char *buffer, char *src, int *buffer_length);
void character_creation_loop(window_info *wi);
void exec_new_game(void);
void exec_load_game();
void exec_exit();

extern enum game_mode mode;
extern menu_option menu_options[100];

#endif