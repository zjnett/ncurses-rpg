#ifndef CHARACTER_H
#define CHARACTER_H

#include "rpg.h"

// class name lookup table
static char *class_lookup[4] = { "WARRIOR", "WIZARD", "ROGUE", "RANGER" };

// race name lookup table
static char *race_lookup[4] = { "HUMAN", "ELF", "DWARF", "DEVIL" };

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
    char class_description[MAX_SIZE];
} character_class;

typedef struct character_race {
    character_race_id id;
    char race_name[100];
    char race_description[MAX_SIZE];
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

    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    level level;

} character;

static inline void init_character(character *c) {
    memset(c, 0, sizeof(character));
}

#endif