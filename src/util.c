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

static uint16_t global_data_size = 1;


// Initialize global data array.
void init_global_game_data(void)
{
    // malloc global data array
    global_data = (void **) malloc (global_data_size * sizeof(void *));
    // initialize and malloc global data array members
    player_character = (character *) malloc (sizeof(character));
    global_data[0] = player_character;
}

// Free all global data pointers.
void destroy_global_game_data(void)
{
    for (int i = 0; i < global_data_size; i++)
    {
        free(global_data[i]);
    }
}