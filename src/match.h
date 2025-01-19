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

typedef enum InputState {
    Normal = 0,
    BadInput = Normal - 2,
    IllegalPoint = Normal - 1
}
InputState;

/* A high-level type which describes a match containing different information. */
typedef struct MatchInfo {
    TurnInfo    _turn;
    State       _status;
    Player      _players[2];
    Table       _environment;
}
MatchInfo;

// Prints the whole match on the screen
void PrintMatch(const MatchInfo &match, const Coordinates &legals);

// Initializes a match.
void InitializeMatch(MatchInfo &match);
void InitializeMatch(MatchInfo &match, int width, int height, const TurnInfo &init = PLAYER_USER);
void InitializeMatch(MatchInfo &match, int width, int height, const Text &userName, const Text &opponentName, const TurnInfo &init = PLAYER_USER);

// Gets the players' name.
void InputPlayersName(MatchInfo &match);

// Gets data from the player.
int GetMatchInput(std::istream &stream, MatchInfo &match, const Coordinates &legals, InputState &state);

// Deletes an existing match from the memory.
void Delete(MatchInfo &game);

// Checks if a match can continue.
bool MatchContinues(MatchInfo &game);

// Evaluates the result of a match.
void EvaluateResult(MatchInfo &match);

// Serializes the match information into the stream.
std::ostream& WriteMatch(std::ostream &stream, const MatchInfo &match);
std::istream& ReadMatch(std::istream &stream, MatchInfo &match);

// Saves the current workspace to a temporary file.
bool SaveGame(const MatchInfo &match);
bool LoadGame(MatchInfo &match);
bool GameExists();

// Gives access to the file containing savegames.
Text GetSavegameFile();

// Narrates the result of the game.
void NarrateResult(const MatchInfo &match);

// Initalizes a new match.
void CreateNewGame(MatchInfo &match);

#endif