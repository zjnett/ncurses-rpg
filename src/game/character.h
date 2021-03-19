#ifndef CHARACTER_H
#define CHARACTER_H

// TODO: create xp roadmap
typedef struct _level {
    int level;
    double cumulative_xp;
    double xp_this_level;
} level;

// TODO: think of more items to be added
typedef struct _character {
    char name[100];
    char race[100];
    
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

#endif