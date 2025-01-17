#ifndef GAME_H
#define GAME_H

#define PLAYER_USER 0
#define PLAYER_OPPONENT 1

#include "text.h"
#include "table.h"
#include "coordinates.h"

#define PLAYER_COLOR BrightBlue
#define OPPONENT_COLOR BrightRed

/* A basic type containing different information about a player in the game. */
typedef struct Player {
    Text    _name;
    Size    _count;
}
Player;

typedef int Piece;
typedef int TurnInfo;

/* A high-level type which describes the result of a match. */
typedef enum State {
    Undefined = -1,
    UserWon = PLAYER_USER,
    OpponentWon = PLAYER_OPPONENT,
    GameDraw = PLAYER_OPPONENT + 1
}
State;

typedef enum Error {
    NoError = 0,
    BadInput = NoError - 2,
    IllegalPoint = NoError - 1
}
Error;

/* A high-level type which describes a match containing different information. */
typedef struct MatchInfo {
    TurnInfo    _turn;
    Error       _error;
    State       _status;
    Player      _players[2];
    Table       _environment;
}
MatchInfo;

// typedef MatchInfo* Match;

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
void PrintMatch(const MatchInfo &match);

// Updates the surrounded pieces between two opponents beginning from point
void UpdateSurroundedPieces(Table &, const Point &);

// Destroys a player
void Destroy(Player &);

// Puts a piece in a specific position in the table.
void PutPiece(Table &, const Point &, TurnInfo &);

// Creates a new game.
MatchInfo* Define(int width, int height, const TurnInfo &initial = PLAYER_USER);
MatchInfo* Define(int width, int height, const Text &playerName, const Text &opponentName, const TurnInfo &initial = PLAYER_USER);

// Deletes an existing game from the memory.
void Delete(MatchInfo *game);

// Executes an existing game.
void Execute(MatchInfo &game);

// Checks if a match can continue.
bool MatchContinues(const MatchInfo &game);

// Serializes the player into the stream.
std::ofstream& WritePlayer(std::ofstream &stream, const Player &data);
std::ifstream& ReadPlayer(std::ifstream &stream, Player &data);

// Serializes the match information into the stream.
std::ofstream& WriteMatch(std::ofstream &stream, const MatchInfo &match);
std::ifstream& ReadMatch(std::ifstream &stream, MatchInfo &match);

// Saves the current workspace to a temporary file.
bool SaveGame(const MatchInfo &match);
bool LoadGame(MatchInfo &match);
bool GameExists();

#endif