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

int do_game_loop(window_info *wi)
{

    int input = '\0';
    char buffer[MAX_SIZE] = {'\0'};
    int buf_len = 0;
    int selected_option = 0;

    // function pointers
    void (*func_ptr_array[3])() = {exec_new_game, exec_load_game, exec_exit };

    do
    {
        clear();
        //mvprintw(0, 0, "mode is: %d", mode);

        switch (mode)
        {
        case MAIN_MENU:
            // render main menu
            // FIXME: should not init menu options every time, but also reset is_selected values of menu members
            init_main_menu_options(func_ptr_array);
            select_menu_option(selected_option);
            render_main_menu(wi);
            break;

        case GAMEPLAY:
            // render gameplay
            //update_buffer(buffer, "Gameplay!", &buf_len);
            //mvaddstr(wi->center_rows, wi->center_cols - buf_len, buffer);
            init_character_creation_options();
            character_creation_loop(wi);
            break;

        case MENU:
            // render a game menu
            update_buffer(buffer, "Menu!", &buf_len);
            mvaddstr(wi->center_rows, wi->center_cols - buf_len, buffer);
            break;

        case EXIT:
            // render a goodbye screen?
            break;
        }

        input = wgetch(stdscr);

        process_menu_input(input, &selected_option);

    } while (input != 'q' && mode != EXIT);

    endwin();
    return EXIT_SUCCESS;
}

void character_creation_loop(window_info *wi) {
    int character_creation_completed = 0, selected_field = 0;
    int input = 0;
    character new_player_character;
    init_character(&new_player_character);
    do {
        //clear();

        select_cc_menu_option(selected_field);
        render_character_creation_menu(wi, selected_field, &new_player_character);

        input = wgetch(stdscr);

        switch(input) {
            case KEY_UP:
                if (selected_field == 0)
                    selected_field = num_cc_options - 1;
                else
                    selected_field--;
                break;
            case KEY_DOWN:
                if (selected_field == num_cc_options - 1)
                    selected_field = 0;
                else
                    selected_field++;
                break;
            case 10: // enter
                character_creation_options[selected_field].ptr();
                break;
        }

    } while(!character_creation_completed);
}

void gameplay_render_loop() {

}

int update_buffer(char *buffer, char *src, int *buffer_length)
{
    int n = strlen(src);
    if (n < MAX_SIZE)
    {
        if (strcmp(buffer, src)) // only copy if buffer != src
            strncpy(buffer, src, n + 1);
        *buffer_length = strlen(buffer);
        return 0;
    }
    return 1;
}

void exec_new_game()
{
    mode = GAMEPLAY;
}

void exec_load_game()
{
    mode = MENU;
}

void exec_exit() {
    mode = EXIT;
}