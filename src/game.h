#ifndef GAME_H
#define GAME_H

#define PLAYER_USER 0
#define PLAYER_OPPONENT 1

#include "text.h"
#include "table.h"
#include "coordinates.h"

/* A basic type containing different information about a player in the game. */
typedef struct Player {
    Text    _name;
    Size    _count;
}
Player;

typedef int Piece;
typedef int TurnInfo;

// Destroys a player
void Destroy(Player &);

// Checks if a point is legal for a specific player
bool IsLegal(const Table &, Piece, const Point &);

// Toggles the turn
void ToggleTurn(TurnInfo &turn);

// Returns a list of legal points for a player.
Coordinates GetLegalPoints(const Table &, Piece);

// Updates the count of players' occurrences in the othello table.
void UpdatePlayersCount(const Table &, Player *);

// Updates the surrounded pieces between two opponents beginning from point
void UpdateSurroundedPieces(Table &, const Point &);

// Puts a piece in a specific position in the table.
void PutPiece(Table &, const Point &, TurnInfo &);

// Serializes the player into the stream.
std::ifstream& ReadPlayer(std::ifstream &stream, Player &data);
std::ofstream& WritePlayer(std::ofstream &stream, const Player &data);

#endif