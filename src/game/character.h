#ifndef CHARACTER_H
#define CHARACTER_H

#include "rpg.h"

// ability score define constants (array indexing)
typedef enum _ability_score {
    STR = 0,
    DEX = 1,
    CON = 2,
    INT = 3,
    WIS = 4,
    CHA = 5
} ability_score;

// class name lookup table
const static char * const class_lookup[4] = { "WARRIOR", "WIZARD", "ROGUE", "RANGER" };

// race name lookup table
const static char * const race_lookup[4] = { "HUMAN", "ELF", "DWARF", "DEVIL" };

const static char * const race_bonuses[4] = { "+2 CON, +1 WIS", "+2 DEX, +1 INT", "+2 STR, +1 CON", "+2 CHA, +1 DEX" };

const static int num_races = 4;

const static int num_classes = 4;

typedef enum _character_class_id {
    WARRIOR,
    WIZARD,
    ROGUE,
    RANGER
} character_class_id;

typedef enum _character_race_id {
    HUMAN,
    ELF,
    DWARF,
    DEVIL
} character_race_id;

typedef struct character_class {
    character_class_id id;
    char class_name[100];
    char class_description[MAX_SIZE]; // probably don't need this
} character_class;

typedef struct character_race {
    character_race_id id;
    char race_name[100];
    char race_description[MAX_SIZE]; // probably don't need this, read from file
    int racial_modifier_array[6];
} character_race;

// TODO: create xp roadmap
typedef struct _level {
    int level;
    double cumulative_xp;
    double xp_this_level;
} level;

// TODO: think of more items to be added
typedef struct _character {
    char name[100];

    character_race race;
    character_class class;
    
    int max_hp;
    int current_hp;

    int max_stamina;
    int current_stamina;

    int max_magic;
    int current_magic;

    // could refactor these into ability score & mod arrays
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    int str_mod;
    int dex_mod;
    int con_mod;
    int int_mod;
    int wis_mod;
    int cha_mod;

    level level;

} character;

static inline void init_character(character *c) {
    memset(c, 0, sizeof(character));
}

void select_pc_race(character *pc, int race_option);
void select_pc_class(character *pc, int class_option);
void roll_ability_score(int ability_score_rolls[6][4], int roll_num);
void init_ability_scores(character *pc);
void calculate_ability_scores_and_mods(character *pc, int ability_score_rolls[6][4]);
void calculate_mods(character *pc);
int find_min_index(int array[4]);
int find_modifier(int value);
void copy_player_character(character *pc);

character *player_character;

#endif
