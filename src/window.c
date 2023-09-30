#include "game/window.h"

void window_print_centered_string(WINDOW *w, window_info wi, char *str) {
    mvwaddstr(w, wi.center_rows, wi.center_cols - (strlen(str) / 2), str);
}

void warning_popup_window(window_info *wi, char *warning_str) {
    window_info p_info = { (wi->max_rows/2.5), (wi->max_cols/3), (wi->max_rows/2.5)/2, (wi->max_cols/3)/2 };
    WINDOW *p = newwin(p_info.max_rows, p_info.max_cols, 
                        wi->center_rows - (p_info.center_rows), 
                        wi->center_cols - (p_info.center_cols));
    PANEL *p_panel = new_panel(p);

    box(p, '|', '-');

    update_panels();

    window_print_centered_string(p, p_info, warning_str);

    mvwaddstr(p, p_info.center_rows+1, p_info.center_cols - 14, "Press any key to continue...");

    wgetch(p);

    doupdate();
}
