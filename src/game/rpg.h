#ifndef RPG_H
#define RPG_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <assert.h>
#include <locale.h>
#include <wchar.h>
#include <panel.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define MAX_SIZE 1000

// Credit to user3224237, StackOverflow
// https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses/32794353
#ifndef CTRL
#define CTRL(c) ((c) & 037)
#endif

typedef enum game_mode {
    MAIN_MENU,
    GAMEPLAY,
    MENU,
    EXIT
} game_mode;

#endif