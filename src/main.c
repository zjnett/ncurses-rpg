#include "game/rpg.h"
#include "game/game.h"
#include "game/window.h"

enum game_mode mode;

int main(int argc, char *argv[])
{

    srand(time(NULL));

    // initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    // initialize window info
    window_info wi;
    init_window_info(&wi);

    mode = MAIN_MENU;

    int exit_condition = do_game_loop(&wi);

    exit(exit_condition);

}