#ifndef RPG_H
#define RPG_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <locale.h>
#include <wchar.h>
#include <panel.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define MAX_SIZE 1000

typedef enum game_mode {
    MAIN_MENU,
    GAMEPLAY,
    MENU,
    EXIT
} game_mode;

#endif