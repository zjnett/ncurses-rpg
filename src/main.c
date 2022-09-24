#include "game/rpg.h"
#include "game/game.h"
#include "game/window.h"
#include "game/util.h"

enum game_mode mode;

int main(int argc, char *argv[])
{

    srand(time(NULL));

    setlocale(LC_ALL, "");

    // initialize global data
    init_global_game_data();

    // initialize ncurses
    init_ncurses();

    // initialize color
    init_game_color();

    // initialize window info
    init_window_info();

    mode = MAIN_MENU;

    int exit_condition = do_game_loop(&wi);

    // free all global memory
    destroy_global_game_data();

    exit(exit_condition);

}