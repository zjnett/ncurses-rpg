#include "game/window.h"

// TODO: make resource path a const char*?

// ASCII art generated by tool by patorjk,
// http://patorjk.com/software/taag/
void render_main_menu(window_info *wi) {
    // load main menu into buffer
    int w, h; // logo width and height
    char buffer[MAX_SIZE] = { '\0' };
    FILE *logo = fopen("../res/gfx/ui/logo", "r");
    if (logo != NULL) {
        if (fscanf(logo, "%d,%d", &w, &h) == 2) {
            // only executes if both width and height could be read
            int y = wi->center_rows - (wi->max_rows / 3) + (h/2), x = wi->center_cols - (w / 2);
            //int y = 0, x = 0;
            char cur = fgetc(logo);
            while (cur != EOF) {
                if (cur == '\n') {
                    x = wi->center_cols - (w / 2); // reset x
                    move(++y, x); // add 1 to y, then move cursor
                }
                mvaddch(y, x++, cur); // add character, then iterate x
                cur = fgetc(logo);
            }
        }
        fclose(logo);
    }

    // print menu options
    mvaddstr(wi->center_rows + h, wi->center_cols - 5, "Play Game");
}