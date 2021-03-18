#include "game/game.h"

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
    
    int input = '\0';
    char buffer[MAX_SIZE] = { '\0' };
    int buf_len = 0;
    int selected_option = 0;

    // function pointers
    void (*func_ptr_array[3])() = { exec_new_game, NULL, NULL };

    do {
        clear();
        //mvprintw(0, 0, "mode is: %d", mode);

        switch(mode) {
            case MAIN_MENU:
                // render main menu
                init_main_menu_options(func_ptr_array);
                select_menu_option(selected_option);
                render_main_menu(wi);
                break;

            case GAMEPLAY:
                // render gameplay
                update_buffer(buffer, "Gameplay!", &buf_len);
                mvaddstr(wi->center_rows, wi->center_cols - buf_len, buffer);
                break;

            case MENU:
                // render a game menu
                update_buffer(buffer, "Menu!", &buf_len);
                mvaddstr(wi->center_rows, wi->center_cols - buf_len, buffer);
                break;
        }

        input = getch();

        switch(input) {
            case '1':
                mode = MAIN_MENU;
                break;
            case '2':
                mode = GAMEPLAY;
                break;
            case '3':
                mode = MENU;
                break;
        }

        if (input == KEY_UP) {
            if (selected_option == 0)
                selected_option = 2;
            else
                selected_option--;
        } else if (input == KEY_DOWN) {
            if (selected_option == 2)
                selected_option = 0;
            else
                selected_option++;
        } else if (input == 10) { // ENTER, since KEY_ENTER is for the numpad
            if (selected_option == 2) {
                input = 'q';
                continue;
            }  
            func_ptr_array[selected_option]();
        }

    } while(input != 'q');

    endwin();
    return EXIT_SUCCESS;
}

int update_buffer(char *buffer, char *src, int *buffer_length) {
    int n = strlen(src);
    if (n < MAX_SIZE) {
        if (strcmp(buffer, src)) // only copy if buffer != src
            strncpy(buffer, src, n+1);
        *buffer_length = strlen(buffer);
        return 0;
    }
    return 1;
}

void exec_new_game() {
    mode = GAMEPLAY;
}