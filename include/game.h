#ifndef GAME_H
#define GAME_H

#define PLAYER 0
#define OPPONENT 1

#include "text.h"

/* The player containing different information */
typedef struct Player {
    Text    _name;
    int     _count;
}
Player;

#endif