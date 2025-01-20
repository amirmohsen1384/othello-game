#ifndef SCOREBOARD_IO_H
#define SCOREBOARD_IO_H

#include "core.h"
#include <fstream>
#include <iostream>

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