#include "game/menu.h"

extern menu_option menu_options[100];
extern int num_main_menu_options;

menu_option character_creation_options[100];
int num_cc_options;

int character_creation_verification[100];

void init_main_menu_options(void (*ptr[])())
{
    create_menu_option(&menu_options[0], "New Game", ptr[0], 0);
    create_menu_option(&menu_options[1], "Load Game", ptr[1], 0);
    create_menu_option(&menu_options[2], "Quit", ptr[2], 0);
    num_main_menu_options = 3;
}

void init_verification_options(void) {
    for (int i = 0; i < num_cc_options; i++) {
        character_creation_verification[i] = 0;
    }
}

void verify_options(int num, ...) {
    va_list args;
    va_start(args, num);
    for (int i = 0; i < num; i++) {
        character_creation_verification[va_arg(args, int)] = 1;
    }
    va_end(args);
}

void create_menu_option(menu_option *m, char *name, void *ptr, int is_selected)
{
    strcpy(m->name, name);
    m->ptr = ptr;
    m->name_length = strlen(name);
    m->is_selected = is_selected;
}

// TODO: change this to be 'main menu option'
void select_menu_option(int num)
{
    menu_options[num].is_selected = 1;
}

// TODO: make resource path a const char*?

// ASCII art generated by tool by patorjk,
// http://patorjk.com/software/taag/
void render_main_menu(window_info *wi)
{
    // load main menu into buffer
    int w, h; // logo width and height
    char buffer[MAX_SIZE] = {'\0'};
    FILE *logo = fopen("../res/gfx/ui/logo", "r");
    if (logo != NULL)
    {
        if (fscanf(logo, "%d,%d", &w, &h) == 2)
        {
            // only executes if both width and height could be read
            int y = wi->center_rows - (wi->max_rows / 3) + (h / 2), x = wi->center_cols - (w / 2);
            //int y = 0, x = 0;
            char cur = fgetc(logo);
            while (cur != EOF)
            {
                if (cur == '\n')
                {
                    x = wi->center_cols - (w / 2); // reset x
                    move(++y, x);                  // add 1 to y, then move cursor
                }
                mvaddch(y, x++, cur); // add character, then iterate x
                cur = fgetc(logo);
            }
        }
        fclose(logo);
    }

    // print menu options
    for (int i = 0; i < num_main_menu_options; i++)
    {
        if (menu_options[i].is_selected)
            attron(COLOR_PAIR(6));
        mvaddstr(wi->center_rows + h + i, wi->center_cols - (menu_options[i].name_length / 2), menu_options[i].name);
        attroff(COLOR_PAIR(6)); // turn off color if used
    }
}

void process_menu_input(int input, int *selected_option)
{
    switch (input)
    {
    case KEY_UP:
        if (*selected_option == 0)
            *selected_option = 2;
        else
            (*selected_option)--;
        break;
    case KEY_DOWN:
        if (*selected_option == 2)
            *selected_option = 0;
        else
            (*selected_option)++;
        break;
    case 10: // enter
        menu_options[*selected_option].ptr();
        break;
    }
}

void init_character_creation_options(void) {
    void (*ptr)() = get_character_attribute;
    create_menu_option(&character_creation_options[0], "Name: ", ptr, 0);
    create_menu_option(&character_creation_options[1], "Race: ", ptr, 0);
    create_menu_option(&character_creation_options[2], "Class: ", ptr, 0);
    create_menu_option(&character_creation_options[3], "Roll for ability scores!", ptr, 0);
    num_cc_options = 4;
}

// maybe possible to toggle these on-off instead of systematically looping every game loop?
void select_cc_menu_option(int selected_field) {
    for (int i = 0; i < num_cc_options; i++) {
        character_creation_options[i].is_selected = 0;
    }
    character_creation_options[selected_field].is_selected = 1;
}

void render_character_creation_menu(window_info *wi, int selected_option, character *pc) {
    int initial_y = (wi->max_rows * 0.1), initial_x = (wi->max_cols * 0.1);
    int x = initial_x, y = initial_y;

    int vertical_padding = 3;

    box(stdscr, '|', '-');

    attron(A_BOLD);
    mvaddstr(y++, x, "Attributes:");
    attroff(A_BOLD);

    // update these test values to be actual character parameters
    print_status_bar(y++, x, "HP", 4, pc->current_hp, pc->max_hp);
    print_status_bar(y++, x, "SP", 2, pc->current_stamina, pc->max_stamina);
    print_status_bar(y++, x, "MP", 1, pc->current_magic, pc->max_magic);

    y += vertical_padding; // move 3 rows down

    char buffer[MAX_SIZE] = { '\0' };

    for (int i = 0; i < num_cc_options; i++) {
        if (character_creation_options[i].is_selected)
            attron(COLOR_PAIR(6));
        prep_formatted_attribute(i, pc, buffer);
        mvaddstr(y++, x, buffer);
        attroff(COLOR_PAIR(6));
    }

    y += vertical_padding;

    attron(A_BOLD);
    mvaddstr(y++, x, "Ability Scores:");
    attroff(A_BOLD);

    // TODO: possible refactor, abs only needed because of ternary operator - printing (no 'empty' character)
    mvprintw(y++, x, "STR: %d (%c%d)", pc->strength, pc->str_mod >= 0 ? '+' : '-', abs(pc->str_mod));
    mvprintw(y++, x, "DEX: %d (%c%d)", pc->dexterity, pc->dex_mod >= 0 ? '+' : '-', abs(pc->dex_mod));
    mvprintw(y++, x, "CON: %d (%c%d)", pc->constitution, pc->con_mod >= 0 ? '+' : '-', abs(pc->con_mod));
    mvprintw(y++, x, "INT: %d (%c%d)", pc->intelligence, pc->int_mod >= 0 ? '+' : '-', abs(pc->int_mod));
    mvprintw(y++, x, "WIS: %d (%c%d)", pc->wisdom, pc->wis_mod >= 0 ? '+' : '-', abs(pc->wis_mod));
    mvprintw(y++, x, "CHA: %d (%c%d)", pc->charisma, pc->cha_mod >= 0 ? '+' : '-', abs(pc->cha_mod));

    // always print commands in bold color, right at the bottom

    // the random colors are kind of tacky, so i might get rid of them
    // (i also like them, though)
    attron(A_BOLD);
    attron(COLOR_PAIR(rand() % 6 + 1));
    mvaddstr(wi->max_rows - 3, x, "ARROW KEYS + ENTER to SELECT | CTRL+H for HELP | CTRL+D to FINISH");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(rand() % 6 + 1));
}

void prep_formatted_attribute(int id, character *pc, char *dest) {
    memset(dest, 0, MAX_SIZE);
    strcpy(dest, character_creation_options[id].name);
    switch(id) {
        case 0: // name
            strcat(dest, pc->name);
            break;
        case 1: // race
            strcat(dest, race_lookup[pc->race.id]);
            break;
        case 2: // class
            strcat(dest, class_lookup[pc->class.id]);
            break;

    }
}

void print_status_bar(int y, int x, char *name, short color_code, int actual, int nominal) {
    mvprintw(y, x, "%s: ", name);
    x += strlen(name) + 2; // move over x coordinates by name len + 2 (: and space)
    attron(COLOR_PAIR(color_code));

    double ratio = (double) actual / nominal;
    int red_nominal = 30, red_actual = red_nominal * ratio;
    
    for (int i = 0; i < red_nominal; i++) {
        if (i <= red_actual)
            mvprintw(y, x, "%lc", 0x2588);
        else
            mvprintw(y, x, "%lc", 0x2591);
        x++;
    }
    x += 1; // move one more space over
    attroff(COLOR_PAIR(color_code));
    mvprintw(y, x, "%d / %d", actual, nominal);
}

void render_dialogue_menu() {

}

void gets_window(window_info *wi, char *name, char *dest) {
    char str[100] = { '\0' };
    memset(dest, 0, strlen(dest)+1);

    sprintf(str, "Enter a %s: ", name);

    window_info p_info = { (wi->max_rows/2), (wi->max_cols/2), (wi->max_rows/2)/2, (wi->max_cols/2)/2 };
    WINDOW *p = newwin(p_info.max_rows, p_info.max_cols, 
                        wi->center_rows - (p_info.center_rows), 
                        wi->center_cols - (p_info.center_cols));
    PANEL *p_panel = new_panel(p);

    box(p, '|', '-');

    update_panels();

    mvwaddstr(p, p_info.center_rows, p_info.center_cols - strlen(str), str);

    echo();
    curs_set(1);

    wgetstr(p, dest);

    doupdate();

    noecho();
    curs_set(0);
}

int getint_window() {
    return 0;
}

// probably not going to be used
int find_selected_cc_option(void) {
    for (int i = 0; i < num_cc_options; i++) {
        if (character_creation_options[i].is_selected)
            return i;
    }
    return -1;
}

void get_character_attribute(character *pc, int selected_option) {
    if (!strncmp(character_creation_options[selected_option].name, "Name", 4)) {
        gets_window(&wi, "name", pc->name);
        character_creation_verification[0] = 1;
    } else if (!strncmp(character_creation_options[selected_option].name, "Race", 4)) {
        race_selection_window(&wi, pc);
        character_creation_verification[1] = 1;
    } else if (!strncmp(character_creation_options[selected_option].name, "Class", 5)) {
        class_selection_window(&wi, pc);
        character_creation_verification[2] = 1;
    } else if (!strncmp(character_creation_options[selected_option].name, "Roll", 4)) {
        // ability score rolling
        ability_score_roll_window(&wi, pc);
        character_creation_verification[3] = 1;
    }
}

void race_selection_window(window_info *wi, character *pc) {

    window_info p_info = { (wi->max_rows/1.5), (wi->max_cols/1.7), (wi->max_rows/1.5)/2, (wi->max_cols/1.7)/2 };
    WINDOW *p = newwin(p_info.max_rows, p_info.max_cols, 
                        wi->center_rows - (p_info.center_rows), 
                        wi->center_cols - (p_info.center_cols));
    PANEL *p_panel = new_panel(p);

    keypad(p, true);
    box(p, '|', '-');

    // Initial horizontal margin of 0.5%, paragraph margin of 2%, line break at 80% of max.
    int initial_x_margin = (ceil(p_info.max_cols * 0.05)), initial_y_margin = (ceil(p_info.max_rows * 0.1)), 
        para_margin = (p_info.max_cols * 0.15), line_break = (p_info.max_cols * 0.9);

    int input = 0, race_option = pc->race.id;
    char dummy[10];

    char race_descriptions[1000][4];

    // read descriptions into array from file
    // this is only done once to save on I/O
    FILE *race_desc_file = fopen("../res/text/desc/races", "r");
    if (race_desc_file != NULL) {
        for (int i = 0; i < num_races; i++) {
            // read in dummy string from file
            fscanf(race_desc_file, "%s\n", dummy);
            char cur = fgetc(race_desc_file);
            int count = 0;
            while (cur != '\n')
            {
                race_descriptions[count++][i] = cur;
                cur = fgetc(race_desc_file);
            }
            race_descriptions[count][i] = '\0';
        }
        fclose(race_desc_file);
    }

    while (input != 10) { // not enter
        int y = initial_y_margin, x = initial_x_margin;
        update_panels();
        // TODO: change so the only printed description is the selected option

        for (int i = 0; i < num_races; i++) {
            x = initial_x_margin;
            if (race_option == i)
                wattron(p, COLOR_PAIR(3));
            mvwaddstr(p, y, x, race_lookup[i]);
            wattron(p, COLOR_PAIR(2));
            wprintw(p, "\t\t%s", race_bonuses[i]);
            wattroff(p, COLOR_PAIR(2));
            y++;
            // move x to paragraph margin
            x = para_margin;
            wmove(p, y, x);
            if (race_option == i)
                wattron(p, COLOR_PAIR(3));
            for (int j = 0; race_descriptions[j][i] != '\0'; j++) {
                if (x > line_break && race_descriptions[j][i] == ' ') {
                    x = para_margin;          // reset x
                    wmove(p, ++y, x);         // add 1 to y, then move cursor
                }
                mvwaddch(p, y, x++, race_descriptions[j][i]); // add character, then iterate x
            }
            wattroff(p, COLOR_PAIR(3));
            y++;
        }

        input = wgetch(p);

        // TODO: refactor this menu switch statement? i feel like this is the third time
        // probably can go in its own function with selected_option as an output parameter
        switch(input) {
        case KEY_UP:
            if (race_option == 0)
                race_option = num_races - 1;
            else
                race_option--;
            break;
        case KEY_DOWN:
            if (race_option == num_races - 1)
                race_option = 0;
            else
                race_option++;
            break;
        case 10: // enter
            select_pc_race(pc, race_option);
            calculate_mods(pc);
            continue;
        }

        doupdate();
    }

    
}

void class_selection_window(window_info *wi, character *pc) {
    window_info p_info = { (wi->max_rows/1.5), (wi->max_cols/1.7), (wi->max_rows/1.5)/2, (wi->max_cols/1.7)/2 };
    WINDOW *p = newwin(p_info.max_rows, p_info.max_cols, 
                        wi->center_rows - (p_info.center_rows), 
                        wi->center_cols - (p_info.center_cols));
    PANEL *p_panel = new_panel(p);

    keypad(p, true);
    box(p, '|', '-');

    // Initial horizontal margin of 0.5%, paragraph margin of 2%, line break at 80% of max.
    int initial_x_margin = (ceil(p_info.max_cols * 0.05)), initial_y_margin = (ceil(p_info.max_rows * 0.1)), 
        para_margin = (p_info.max_cols * 0.2), line_break = (p_info.max_cols * 0.9);

    int input = 0, class_option = pc->class.id;
    char dummy[10];

    while (input != 10) { // not enter
        int y = initial_y_margin, x = initial_x_margin;
        update_panels();

        for (int i = 0; i < num_classes; i++) {
            x = initial_x_margin;
            if (class_option == i)
                wattron(p, COLOR_PAIR(3));
            mvwaddstr(p, y++, x, class_lookup[i]);
            wattroff(p, COLOR_PAIR(3));
            // move x to paragraph margin
            //x = para_margin;
            //wmove(p, y, x);
            y++;
        }

        input = wgetch(p);

        switch(input) {
        case KEY_UP:
            if (class_option == 0)
                class_option = num_classes - 1;
            else
                class_option--;
            break;
        case KEY_DOWN:
            if (class_option == num_classes - 1)
                class_option = 0;
            else
                class_option++;
            break;
        case 10: // enter
            select_pc_class(pc, class_option);
            continue;
        }

        doupdate();
    }
}

void ability_score_roll_window(window_info *wi, character *pc) {
    window_info p_info = { (wi->max_rows/1.5), (wi->max_cols/1.7), (wi->max_rows/1.5)/2, (wi->max_cols/1.7)/2 };
    WINDOW *p = newwin(p_info.max_rows, p_info.max_cols, 
                        wi->center_rows - (p_info.center_rows), 
                        wi->center_cols - (p_info.center_cols));
    PANEL *p_panel = new_panel(p);

    keypad(p, true);
    box(p, '|', '-');

    int ability_score_rolls[6][4] = { { 0 } };

    int initial_x_margin = (ceil(p_info.max_cols * 0.05)), initial_y_margin = (p_info.center_rows) - 3, 
        para_margin = (p_info.max_cols * 0.2), line_break = (p_info.max_cols * 0.9);

    int input = 0, class_option = pc->class.id;
    char dummy[10];
    int has_rolled = 0;

    while (input != 10) { // not enter
        int y = initial_y_margin, x = initial_x_margin;
        update_panels();

        wattron(p, COLOR_PAIR(5));
        mvwaddstr(p, 0, p_info.center_cols - 18, "Press 'R' to roll dice values!");
        wattroff(p, COLOR_PAIR(5));

        // TODO: possible refactor, abs only needed because of ternary operator - printing (no 'empty' character)
        mvwprintw(p, y++, x, "STR: %d (%c%d)", pc->strength, pc->str_mod >= 0 ? '+' : '-', abs(pc->str_mod));
        mvwprintw(p, y++, x, "DEX: %d (%c%d)", pc->dexterity, pc->dex_mod >= 0 ? '+' : '-', abs(pc->dex_mod));
        mvwprintw(p, y++, x, "CON: %d (%c%d)", pc->constitution, pc->con_mod >= 0 ? '+' : '-', abs(pc->con_mod));
        mvwprintw(p, y++, x, "INT: %d (%c%d)", pc->intelligence, pc->int_mod >= 0 ? '+' : '-', abs(pc->int_mod));
        mvwprintw(p, y++, x, "WIS: %d (%c%d)", pc->wisdom, pc->wis_mod >= 0 ? '+' : '-', abs(pc->wis_mod));
        mvwprintw(p, y++, x, "CHA: %d (%c%d)", pc->charisma, pc->cha_mod >= 0 ? '+' : '-', abs(pc->cha_mod));

        input = wgetch(p);

        switch(input) {
        case 'r':
        case 'R':
            roll_ability_score_window(wi, ability_score_rolls);
            calculate_ability_scores_and_mods(pc, ability_score_rolls);
            has_rolled = 1;
            break;

        case 10: // enter
            continue;
        }

        doupdate();
    }
}

void roll_ability_score_window(window_info *wi, int ability_score_rolls[6][4]) {
    window_info p_info = { (wi->max_rows/2.5), (wi->max_cols/3), (wi->max_rows/2.5)/2, (wi->max_cols/3)/2 };
    WINDOW *p = newwin(p_info.max_rows, p_info.max_cols, 
                        wi->center_rows - (p_info.center_rows), 
                        wi->center_cols - (p_info.center_cols));
    PANEL *p_panel = new_panel(p);

    int num_rolls = 0;

    box(p, '|', '-');

    update_panels();

    window_print_centered_string(p, p_info, "NOW ROLLING...");

    int initial_y = p_info.center_rows+1, initial_x = p_info.center_cols;
    int y = initial_y, x = initial_x;
    int stop = 0;

    while (num_rolls < 6) {
        stop = 0;
        while (stop != 10) {
            y = initial_y;
            x = initial_x;
            nodelay(p, true);
            mvwaddstr(p, y++, x - 15, "Press ENTER to stop the dice!");
            roll_ability_score(ability_score_rolls, num_rolls);
            mvwprintw(p, y++, x - 4, "%d %d %d %d", ability_score_rolls[num_rolls][0], ability_score_rolls[num_rolls][1], 
                                                    ability_score_rolls[num_rolls][2], ability_score_rolls[num_rolls][3]);
            stop = wgetch(p);
        }
        nodelay(p, false);
        if (num_rolls != 5) {
            mvwprintw(p, y, x - 25, "Roll %d complete! Press any key to roll again...", num_rolls+1);
        } else {
            mvwprintw(p, y, x - 26, "Rolling complete! Press any key to return to setup.");
        }
        wgetch(p);
        num_rolls++;
    }

    doupdate();
    wclear(p);
}

int validate_character_creation_completion(void) {
    for (int i = 0; i < num_cc_options; i++) {
        if (character_creation_verification[i] == 0) {
            return 0;
        }
    }
    return 1;
}
