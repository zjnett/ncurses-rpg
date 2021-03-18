#include "game/game.h"

extern enum game_mode mode;

/*
        RENDER LAYERS:

    /===================/|
    |     draw game     ||
    |___________________|/
              
            |
            |
            V
    /===================/|
    |     draw GUI      ||
    |___________________|/

*/

int do_game_loop(window_info *wi) {
    
    char input = '\0';
    char buffer[MAX_SIZE] = { '\0' };
    int buf_len = 0;

    int random = 15;

    do {
        clear();

        switch(mode) {
            case MAIN_MENU:
                // render main menu
                random = rand() % 1000;
                sprintf(buffer, "Main menu! %d", random);
                //update_buffer(buffer, buffer, &buf_len);
                buf_len = strlen(buffer);
                fprintf(stderr, "%s", buffer);
                mvaddstr(wi->center_rows, wi->center_cols - buf_len, buffer);
                break;

            case GAMEPLAY:
                // render gameplay
                update_buffer(buffer, "Game menu!", &buf_len);
                mvaddstr(wi->center_rows - buf_len, wi->center_cols, buffer);
                break;

            case MENU:
                // render a game menu
                update_buffer(buffer, "Menu!", &buf_len);
                mvaddstr(wi->center_rows - buf_len, wi->center_cols, buffer);
                break;
        }

        input = getch();
    } while(input != 'q');

    endwin();
    return EXIT_SUCCESS;
}

int update_buffer(char *buffer, char *src, int *buffer_length) {
    int n = strlen(src);
    if (n < MAX_SIZE) {
        strncpy(buffer, src, n);
        *buffer_length = strlen(buffer);
        return 0;
    }
    return 1;
}