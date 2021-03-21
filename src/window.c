#include "game/window.h"

void window_print_centered_string(WINDOW *w, window_info wi, char *str) {
    mvwaddstr(w, wi.center_rows, wi.center_cols - (strlen(str) / 2), str);
}