#ifndef WINDOW_H
#define WINDOW_H

#include "rpg.h"

typedef struct _window_info {
    int max_rows;
    int max_cols;
    int center_rows;
    int center_cols;
} window_info;

// global window info
window_info wi;

static inline void init_window_info() {
    getmaxyx(stdscr, wi.max_rows, wi.max_cols);
    wi.center_rows = wi.max_rows / 2;
    wi.center_cols = wi.max_cols / 2;
}

#endif