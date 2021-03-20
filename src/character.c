#include "game/character.h"

void select_pc_race(character *pc, int race_option) {
    // fulfill all members of 'race' struct
    pc->race.id = race_option;
    strcpy(pc->race.race_name, race_lookup[race_option]);
}