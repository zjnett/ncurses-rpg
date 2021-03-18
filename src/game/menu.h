#ifndef MENU_H
#define MENU_H

#include "rpg.h"
#include "window.h"

typedef struct _menu_option {
    char name[100];
    void *ptr;
    int name_length;
    int is_selected;
} menu_option;

#define init_menu_option(x) menu_option x = {.name={ '\0' }, .ptr = NULL, .name_length = 0, .is_selected = 0 };

void init_main_menu_options(void);

void create_menu_option(menu_option *m, char *name, void *ptr, int is_selected);

void select_menu_option(int num);

// ASCII art generated by tool by patorjk,
// http://patorjk.com/software/taag/
void render_main_menu(window_info *wi);

// global menu options array
menu_option menu_options[100];
int num_main_menu_options;

#endif