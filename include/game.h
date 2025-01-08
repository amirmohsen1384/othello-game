#ifndef GAME_H
#define GAME_H

#define PLAYER_USER 0
#define PLAYER_OPPONENT 1

#include "table.h"
#include "text.h"

/* The player containing different information */
typedef struct Player {
    Text    _name;
    int     _count;
}
Player;

typedef int PlayerNumber;

// Returns a list of legal points for a player.
Coordinates GetLegalPoints(const Table &, PlayerNumber);

#endif