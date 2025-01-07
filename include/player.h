#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER 0
#define OPPONENT 1

#include "strings.h"

/* The player containing different information */
typedef struct Player {
    String _name;
    int _count;
}
Player;

#endif