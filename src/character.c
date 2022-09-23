#include "game/character.h"

void select_pc_race(character *pc, int race_option) {
    // fulfill all members of 'race' struct
    remove_current_racial_mods(pc); // remove old racial mods
    pc->race.id = race_option;
    strcpy(pc->race.race_name, race_lookup[race_option]);
    //reset_pc_ability_scores(pc);
    calculate_racial_mods(pc);
    add_racial_mods(pc); // calculate new racial mods
    calculate_character_attributes(pc);
    calculate_mods(pc);
}

void calculate_racial_mods(character *pc) {
    // compute modifier and place it in racial_mods array
    // [STR, DEX, CON, INT, WIS, CHA]
    // [ 0,   1,   2,   3,   4,   5 ]
    reset_racial_mods(pc);
    switch(pc->race.id) {
        case HUMAN: // con +2, wis +1
            pc->race.racial_modifier_array[CON] = 2;
            pc->race.racial_modifier_array[WIS] = 1;
            break;
        case ELF: // dex +2, int +1
            pc->race.racial_modifier_array[DEX] = 2;
            pc->race.racial_modifier_array[INT] = 1;
            break;
        case DWARF: // str+2, con+1
            pc->race.racial_modifier_array[STR] = 2;
            pc->race.racial_modifier_array[CON] = 1;
            break;
        case DEVIL: // cha+2, dex+1
            pc->race.racial_modifier_array[CHA] = 2;
            pc->race.racial_modifier_array[DEX] = 1;
            break;
    }
}

void reset_racial_mods(character *pc) {
    for (int i = 0; i < 6; i++) {
        pc->race.racial_modifier_array[i] = 0;
    }
}

void reset_pc_ability_scores(character *pc) {
    pc->strength = 0;
    pc->dexterity = 0;
    pc->constitution = 0;
    pc->intelligence = 0;
    pc->wisdom = 0;
    pc->charisma = 0;
}

void select_pc_class(character *pc, int class_option) {
    // fulfill members of 'class' struct
    pc->class.id = class_option;
    strcpy(pc->class.class_name, class_lookup[class_option]);
}

void calculate_character_attributes(character *pc) {
    pc->max_hp = 10 + (abs(pc->constitution)*5);
    pc->max_stamina = 10 + (abs(pc->dexterity)*5);
    if (pc->race.id == HUMAN) {
        pc->max_magic = 10 + (abs(pc->wisdom)*5);
    } else if (pc->race.id == DEVIL) {
        pc->max_magic = 10 + (abs(pc->charisma)*5);
    } else {
        pc->max_magic = 10 + (abs(pc->intelligence)*5);
    }
    //pc->current_hp = pc->max_hp * 0.25;
    //pc->current_stamina = pc->max_stamina * 0.5;
    //pc->current_magic = pc->max_magic * 0.75;
    pc->current_hp = pc->max_hp;
    pc->current_stamina = pc->max_stamina;
    pc->current_magic = pc->max_magic;
}

void roll_ability_score(int ability_score_rolls[6][4], int roll_num) {
    for (int i = 0; i < 4; i++) {
        ability_score_rolls[roll_num][i] = rand() % 6 + 1;
    }
}

void init_ability_scores(character *pc) {
    pc->strength = 0 + pc->race.racial_modifier_array[STR];
    pc->dexterity = 0 + pc->race.racial_modifier_array[DEX];
    pc->constitution = 0 + pc->race.racial_modifier_array[CON];
    pc->intelligence = 0 + pc->race.racial_modifier_array[INT];
    pc->wisdom = 0 + pc->race.racial_modifier_array[WIS];
    pc->charisma = 0 + pc->race.racial_modifier_array[CHA];
}

void calculate_ability_scores_and_mods(character *pc, int ability_score_rolls[6][4]) {
    int ability_scores[6];
    int ability_score_mods[6];

    reset_pc_ability_scores(pc);
    calculate_racial_mods(pc);
    add_racial_mods(pc);

    // sum score values
    for (int i = 0; i < 6; i++) {
        ability_scores[i] = ability_score_rolls[i][0] + ability_score_rolls[i][1] + ability_score_rolls[i][2] + ability_score_rolls[i][3];
        // subtract min value from result
        ability_scores[i] -= ability_score_rolls[i][find_min_index(ability_score_rolls[i])];
        //ability_scores[i] += pc->race.racial_modifier_array[i]; // add racial bonuses to ability scores
    }

    // fulfill ability scores (arbitrarily for now)
    // TODO: don't make this arbitrary
    pc->strength += ability_scores[0];
    pc->dexterity += ability_scores[1];
    pc->constitution += ability_scores[2];
    pc->intelligence += ability_scores[3];
    pc->wisdom += ability_scores[4];
    pc->charisma += ability_scores[5];

    calculate_mods(pc);
    calculate_character_attributes(pc);
}

void calculate_mods(character *pc) {
    pc->str_mod = find_modifier(pc->strength);
    pc->dex_mod = find_modifier(pc->dexterity);
    pc->con_mod = find_modifier(pc->constitution);
    pc->int_mod = find_modifier(pc->intelligence);
    pc->wis_mod = find_modifier(pc->wisdom);
    pc->cha_mod = find_modifier(pc->charisma);
}

void remove_current_racial_mods(character *pc) {
    pc->strength -= pc->race.racial_modifier_array[STR];
    pc->dexterity -= pc->race.racial_modifier_array[DEX];
    pc->constitution -= pc->race.racial_modifier_array[CON];
    pc->intelligence -= pc->race.racial_modifier_array[INT];
    pc->wisdom -= pc->race.racial_modifier_array[WIS];
    pc->charisma -= pc->race.racial_modifier_array[CHA];
}

void add_racial_mods(character *pc) {
    pc->strength += pc->race.racial_modifier_array[STR];
    pc->dexterity += pc->race.racial_modifier_array[DEX];
    pc->constitution += pc->race.racial_modifier_array[CON];
    pc->intelligence += pc->race.racial_modifier_array[INT];
    pc->wisdom += pc->race.racial_modifier_array[WIS];
    pc->charisma += pc->race.racial_modifier_array[CHA];
}

int find_min_index(int array[4]) {
    int min = array[0], min_index = 0;
    for (int i = 1; i < 4; i++) {
        if (array[i] < min) {
            min = array[i];
            min_index = i;
        }
    }
    return min_index;
}

int find_modifier(int value) {
    switch(value) {
        case 20:
            return +5;
        case 19:
        case 18:
            return +4;
        case 17:
        case 16:
            return +3;
        case 15:
        case 14:
            return +2;
        case 13:
        case 12:
            return +1;
        case 11:
        case 10:
            return 0;
        case 9:
        case 8:
            return -1;
        case 7:
        case 6:
            return -2;
        case 5:
        case 4:
            return -3;
        case 3:
        case 2:
            return -4;
        case 1:
            return -5;
    }
    return 0;
}

void copy_player_character(character *pc) {
    memcpy(player_character, pc, sizeof(character));
}