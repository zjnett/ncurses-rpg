#include "game/character.h"

void select_pc_race(character *pc, int race_option) {
    // fulfill all members of 'race' struct
    pc->race.id = race_option;
    strcpy(pc->race.race_name, race_lookup[race_option]);
    reset_pc_ability_scores(pc);
    switch(race_option) {
        case HUMAN:
            pc->constitution += 2;
            pc->wisdom += 1;
            break;
        case ELF:
            pc->dexterity += 2;
            pc->intelligence += 1;
            break;
        case DWARF:
            pc->strength += 2;
            pc->constitution += 1;
            break;
        case DEVIL:
            pc->charisma += 2;
            pc->dexterity += 1;
            break;
    }
    calculate_character_attributes(pc);
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

// TODO: make mods instead of raw scores
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

void calculate_ability_scores_and_mods(character *pc, int ability_score_rolls[6][4]) {
    int ability_scores[6];
    int ability_score_mods[6];

    // sum score values
    for (int i = 0; i < 6; i++) {
        ability_scores[i] = ability_score_rolls[i][0] + ability_score_rolls[i][1] + ability_score_rolls[i][2] + ability_score_rolls[i][3];
        // subtract min value from result
        ability_scores[i] -= ability_score_rolls[i][find_min_index(ability_score_rolls[i])];
    }

    // fulfill ability scores (arbitrarily for now)
    // TODO: don't make this arbitrary
    pc->strength += ability_scores[0];
    pc->dexterity += ability_scores[1];
    pc->constitution += ability_scores[2];
    pc->intelligence += ability_scores[3];
    pc->wisdom += ability_scores[4];
    pc->charisma += ability_scores[5];

    pc->str_mod = find_modifier(pc->strength);
    pc->dex_mod = find_modifier(pc->dexterity);
    pc->con_mod = find_modifier(pc->constitution);
    pc->int_mod = find_modifier(pc->intelligence);
    pc->wis_mod = find_modifier(pc->wisdom);
    pc->cha_mod = find_modifier(pc->charisma);
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