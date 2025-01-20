#ifndef SCOREBOARD_CORE_H
#define SCOREBOARD_CORE_H

#include "game.h"

typedef float FillRatio;

// This describes a single ranked player with its properties.
typedef struct RankedPlayer {
    Player      _player;
    FillRatio   _ratio;
}
RankedPlayer;

/* Assigns a ranked player to another. */
void Assign(RankedPlayer &target, const RankedPlayer &source);

/* Initializes a ranked player. */
void Initialize(RankedPlayer &player);

/* Initializes a ranked player based on a given player and the area of the table where the player is playing. */
void Initialize(RankedPlayer &player, const Player &target, Dimension area);

/* Returns true if the first ranked players is higher than the other in rank. */
bool IsHigher(const RankedPlayer &one, const RankedPlayer &two);

/* Destroys a ranked player. */
void Destroy(RankedPlayer &player);

typedef uint64_t ElementSize;

// This describes a list of ranked players.
typedef struct Scoreboard {
    RankedPlayer    *_players;
    ElementSize      _count;
}
Scoreboard;

/* Initializes a scoreboard. */
void Initialize(Scoreboard &scoreboard);

/* Destroys a scoreboard. */
void Destroy(Scoreboard &scoreboard);

/* Finds a player in the scoreboard. */
int64_t FindRankedPlayer(const Scoreboard &scoreboard, const Player &player);

/* Adds a player to the scoreboard. */
void AddRankedPlayer(Scoreboard &scoreboard, const RankedPlayer &player);

/* Removes a player from the scoreboard. */
void RemoveRankedPlayer(Scoreboard &scoreboard, ElementSize position);

/* Checks whether a scoreboard is empty or not. */
bool IsEmpty(const Scoreboard &scoreboard);

// Serializes the ranked player into the stream.
std::ostream& WriteRankedPlayer(std::ostream &stream, const RankedPlayer &player);
std::istream& ReadRankedPlayer(std::istream &stream, RankedPlayer &player);

// Serializes the scoreboard into the stream.
std::ostream& WriteScoreboard(std::ostream &stream, const Scoreboard &scoreboard);
std::istream& ReadScoreboard(std::istream &stream, Scoreboard &scoreboard);

// Retrieves the file name of the scoreboard file.
Text GetScoreboardFileName();

// Loads a scoreboard from a file.
bool LoadScoreboard(Scoreboard &scoreboard);

// Saves a scoreboard to a file.
bool SaveScoreboard(const Scoreboard &scoreboard);

#endif