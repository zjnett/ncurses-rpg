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