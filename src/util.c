#include "game/util.h"

// All global data is data that should be able to be mutable 
// from anywhere in the application state.
//
// The primary example of this is the main character object,
// which is declared in character.h.

// Object:  Player character struct data
//          Main player statistics and information.
// File:    character.h
extern character *player_character;

void **global_data;

const static size_t global_data_size = 1;

// Initialize global data array.
void init_global_game_data(void)
{
    // malloc global data array
    global_data = (void **) malloc (global_data_size * sizeof(void *));
    // initialize and malloc global data array members
    player_character = (character *) malloc (sizeof(character));
    global_data[0] = player_character;
    // check that final global data array size is the same as we've declared
    assert(global_data_size == (sizeof(global_data) / sizeof(global_data[0])));
}

// Free all global data pointers.
void destroy_global_game_data(void)
{
    for (size_t i = 0; i < global_data_size; i++)
    {
        free(global_data[i]);
    }
}

// Initial calls to setup ncurses
void init_ncurses(void)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
}

// Enable color and set ncurses color pairs
void init_game_color(void)
{
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
}