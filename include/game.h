#ifndef GAME_H
#define GAME_H

#define PLAYER_USER 0
#define PLAYER_OPPONENT 1

#include "text.h"
#include "table.h"
#include "coordinates.h"

#define EMPTY_COLOR Gray
#define PLAYER_COLOR BrightBlue
#define OPPONENT_COLOR BrightRed
#define VALID_COLOR BrightMagenta

/* A basic type containing different information about a player in the game. */
typedef struct Player {
    Text    _name;
    int     _count;
}
Player;

typedef int Piece;
typedef bool TurnInfo;

/* A high-level type which describes the result of a match. */
typedef enum State {
    Undefined = -1,
    BadInput = Undefined - 2,
    IllegalPoint = Undefined - 1,
    OpponentWon = PLAYER_OPPONENT,
    GameDraw = PLAYER_OPPONENT + 1,
    UserWon = PLAYER_USER
}
State;

/* A high-level type which describes a match containing different information. */
typedef struct MatchInfo {
    TurnInfo    _turn;
    State       _status;
    Player      _players[2];
    Table       _environment;
}* Match;

// Creates a player based on their name
Player* CreatePlayer(const Text &);

// Checks if a point is legal for a specific player
bool IsLegal(const Table &, Piece, const Point &);

// Toggles the turn
void ToggleTurn(TurnInfo &turn);

// Returns a list of legal points for a player.
Coordinates GetLegalPoints(const Table &, Piece);

// Updates the count of players' occurrences in the othello table.
void UpdatePlayersCount(const Table &, Player *);

// Prints the whole match on the screen
void PrintMatch(const Match &match);

// Updates the surrounded pieces between two opponents beginning from point
void UpdateSurroundedPieces(Table &, const Point &);

// Destroys a player
void Destroy(Player &);

// Puts a piece in a specific position in the table.
void PutPiece(Table &, const Point &, TurnInfo &);

// Creates a new game.
Match Define(int width, int height, const TurnInfo &initial = PLAYER_USER);
Match Define(int width, int height, const Text &playerName, const Text &opponentName, const TurnInfo &initial = PLAYER_USER);

// Deletes an existing game from the memory.
void Delete(Match game);

// Executes an existing game.
void Execute(Match game);

// Checks if a match can continue.
bool MatchContinues(Match game);

#endif