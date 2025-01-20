#include "io.h"

std::ostream& WriteRankedPlayer(std::ostream &stream, const RankedPlayer &player) {
    WritePlayer(stream, player._player);
    stream.write(reinterpret_cast<const char*>(&player._ratio), sizeof(FillRatio));
    return stream;
}

std::istream& ReadRankedPlayer(std::istream &stream, RankedPlayer &player) {
    ReadPlayer(stream, player._player);
    stream.read(reinterpret_cast<char*>(&player._ratio), sizeof(FillRatio));
    return stream;
}

std::ostream& WriteScoreboard(std::ostream &stream, const Scoreboard &scoreboard) {
    stream.write(reinterpret_cast<const char*>(&scoreboard._count), sizeof(ElementSize));
    for(ElementSize i = 0; i < scoreboard._count; i++) {
        WriteRankedPlayer(stream, scoreboard._players[i]);
    }
    return stream;
}

std::istream& ReadScoreboard(std::istream &stream, Scoreboard &scoreboard) {
    // Destroys the scoreboard if it is not empty.
    if(!IsEmpty(scoreboard)) {
        Destroy(scoreboard);
    }

    // Reads the number of players in the scoreboard.
    stream.read(reinterpret_cast<char*>(&scoreboard._count), sizeof(ElementSize));
    scoreboard._players = static_cast<RankedPlayer*>(calloc(scoreboard._count, sizeof(RankedPlayer)));
    for(ElementSize i = 0; i < scoreboard._count; i++) {
        ReadRankedPlayer(stream, scoreboard._players[i]);
    }
    return stream;
}

// Retrieves the file name of the scoreboard file.
Text GetScoreboardFileName() {
    const char *fileName = "scoreboard_data.bin";
    Text target = Create(fileName);
    return target;
}

// Loads a scoreboard from a file.
bool LoadScoreboard(Scoreboard &scoreboard) {
    using namespace std;

    // Retrieves the file name of the scoreboard file.
    Text fileName = GetScoreboardFileName();
    ifstream file(fileName._data, ios::binary | ios::in);
    Destroy(fileName);

    // Checks whether the file is open or not.
    if(!file.is_open()) {
        return false;
    }

    // Reads the scoreboard.
    ReadScoreboard(file, scoreboard);
    file.close();
    return true;
}

// Saves a scoreboard to a file.
bool SaveScoreboard(const Scoreboard &scoreboard) {
    using namespace std;

    // Retrieves the file name of the scoreboard file.
    Text fileName = GetScoreboardFileName();
    ofstream file(fileName._data, ios::binary | ios::out);
    Destroy(fileName);

    // Checks whether the file is open or not.
    if(!file.is_open()) {
        return false;
    }

    // Writes the scoreboard.
    WriteScoreboard(file, scoreboard);
    file.close();
    return true;
}
