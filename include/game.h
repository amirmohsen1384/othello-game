#ifndef GAME_H
#define GAME_H

#define PLAYER_USER 0
#define PLAYER_OPPONENT 1

#include "text.h"
#include "table.h"
#include "coordinates.h"

/* The player containing different information */
typedef struct Player {
    Text    _name;
    int     _count;
}
Player;

typedef int Piece;

// Creates a player based on their name
Player* Create(const Text &);

// Checks if a point is legal for a specific player
bool IsLegal(const Table &, Piece, const Point &);

// Returns a list of legal points for a player.
Coordinates GetLegalPoints(const Table &, Piece);

// Updates the count of players' occurrences in the othello table.
void UpdatePlayersCount(const Table &, Player *);

// Prints the whole game on the screen
void PrintGame(const Table &, Player *);

// Updates the surrounded pieces between two opponents beginning from point
void UpdateSurroundedPieces(Table &, const Point &);

// Toggles the color of the piece
void TogglePiece(Cell *);

// Destroys a player
void Destroy(Player &player);

#endif