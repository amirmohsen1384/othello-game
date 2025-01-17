#ifndef MATCH_H
#define MATCH_H

#define PLAYER_USER 0
#define PLAYER_OPPONENT 1

#include "game.h"

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

// Prints the whole match on the screen
void PrintMatch(const MatchInfo &match);

// Creates a new game.
MatchInfo* Define(int width, int height, const TurnInfo &initial = PLAYER_USER);
MatchInfo* Define(int width, int height, const Text &playerName, const Text &opponentName, const TurnInfo &initial = PLAYER_USER);

// Gets the players' name.
void InputPlayersName(MatchInfo &match);

// Fetches data from the player.
void FetchFromPlayer(MatchInfo &match);

// Deletes an existing match from the memory.
void Delete(MatchInfo *game);

// Advances once in the match.
void Advance(MatchInfo &match);

// Checks if a match can continue.
bool MatchContinues(const MatchInfo &game);

// Serializes the match information into the stream.
std::ofstream& WriteMatch(std::ofstream &stream, const MatchInfo &match);
std::ifstream& ReadMatch(std::ifstream &stream, MatchInfo &match);

// Saves the current workspace to a temporary file.
bool SaveGame(const MatchInfo &match);
bool LoadGame(MatchInfo &match);
bool GameExists();

#endif