#include "system.h"
#include <fstream>
#include "match.h"
#include "game.h"

std::ostream& WriteTable(std::ostream &stream, const Table &table) {
    // Write the dimensions of the table
    if(!stream.write(reinterpret_cast<const char*>(&table._width), sizeof(Dimension)).good()) {
        return stream;
    }
    if(!stream.write(reinterpret_cast<const char*>(&table._height), sizeof(Dimension)).good()) {
        return stream;
    }

    // Write the whole table
    if(!stream.write(reinterpret_cast<const char*>(table._data), (table._width * table._height) * sizeof(Cell)).good()) {
        return stream;
    }
    return stream;
}

std::istream& ReadTable(std::istream &stream, Table &table) {
    // Read the dimensions of the table from the stream
    if(!stream.read(reinterpret_cast<char*>(&table._width), sizeof(Dimension)).good()) {
        return stream;
    }
    if(!stream.read(reinterpret_cast<char*>(&table._height), sizeof(Dimension)).good()) {
        return stream;
    }

    // Create a table with the read dimensions.
    Cell *temp = static_cast<Cell*>(calloc(table._width * table._height, sizeof(Cell)));
    if(temp == NULL) {
        table._width = table._height = 0;
        return stream;
    }
    table._data = temp;

    // Read the whole table from the stream.
    if(!stream.read(reinterpret_cast<char*>(table._data), table._width * table._height * sizeof(Cell)).good()) {
        return stream;
    }
    return stream;
}

std::ostream& WriteText(std::ostream &stream, const Text &text) {
    // Writes the length of the text
    if(!stream.write(reinterpret_cast<const char*>(&text._size), sizeof(TextSize)).good()) {
        return stream;
    }

    // Writes the text to the stream
    if(!stream.write(reinterpret_cast<const char*>(text._data), text._size * sizeof(char)).good()) {
        return stream;
    }
    return stream;
}

std::istream& ReadText(std::istream &stream, Text &text) {
    // Reads the length of the text
    if(!stream.read(reinterpret_cast<char*>(&text._size), sizeof(TextSize)).good()) {
        return stream;
    }
    // Reserves the required memory.
    char *temp = static_cast<char*>(realloc(text._data, (text._size + 1) * sizeof(char)));
    if(temp == NULL) {
        text._size = 0;
        return stream;
    }
    text._data = temp;

    // Reads the text from the stream.
    if(!stream.read(reinterpret_cast<char*>(text._data), text._size * sizeof(char)).good()) {
        return stream;
    }

    // Puts the null terminator in the text.
    text._data[text._size] = '\0';
    return stream;
}

std::ostream& WritePlayer(std::ostream &stream, const Player &data) {
    // Writes the points of the player.
    if(!stream.write(reinterpret_cast<const char*>(&data._count), sizeof(PointContainer)).good()) {
        return stream;
    }

    // Writes the name of the player.
    if(!WriteText(stream, data._name).good()) {
        return stream;
    }
    return stream;
}

std::istream& ReadPlayer(std::istream &stream, Player &data) {
    // Reads the points of the player.
    if(!stream.read(reinterpret_cast<char*>(&data._count), sizeof(PointContainer)).good()) {
        return stream;
    }

    // Reads the name of the player.
    if(!ReadText(stream, data._name).good()) {
        return stream;
    }
    return stream;
}

typedef int8_t StateContainer;

std::ostream& WriteMatch(std::ostream &stream, const MatchInfo &match) {
    // Writes the user to the stream
    if(!WritePlayer(stream, match._players[PLAYER_USER]).good()) {
        return stream;
    }

    // Writes the opponent to the stream
    if(!WritePlayer(stream, match._players[PLAYER_OPPONENT]).good()) {
        return stream;
    }

    // Writes the turn to the stream
    if(!stream.write(reinterpret_cast<const char*>(&match._turn), sizeof(TurnInfo)).good()) {
        return stream;
    }

    // Writes the current state of the match to the stream
    StateContainer size = static_cast<StateContainer>(match._status);
    if(!stream.write(reinterpret_cast<const char*>(&size), sizeof(StateContainer)).good()) {
        return stream;
    }

    // Writes the whole table to the stream
    if(!WriteTable(stream, match._environment).good()) {
        return stream;
    }

    return stream;
}

std::istream& ReadMatch(std::istream &stream, MatchInfo &match) {
    // Reads the user from the stream
    if(!ReadPlayer(stream, match._players[PLAYER_USER]).good()) {
        return stream;
    }

    // Reads the opponent from the stream
    if(!ReadPlayer(stream, match._players[PLAYER_OPPONENT]).good()) {
        return stream;
    }

    // Reads the turn from the stream
    if(!stream.read(reinterpret_cast<char*>(&match._turn), sizeof(TurnInfo)).good()) {
        return stream;
    }

    // Read the current state of the match from the stream
    StateContainer value = 0;
    if(!stream.read(reinterpret_cast<char*>(&value), sizeof(StateContainer)).good()) {
        return stream;
    }
    match._status = static_cast<State>(value);

    // Read the whole table from the stream
    if(!ReadTable(stream, match._environment).good()) {
        return stream;
    }

    return stream;
}

typedef uint64_t Magic;
const Magic magic = 0xD3314D;

bool IsFileValid(std::istream &stream, bool ignore = false) {
    Magic value = 0;
    bool result = 0;
    if(!stream.read(reinterpret_cast<char*>(&value), sizeof(Magic)).good()) {
        result = false;
        return result;
    }
    if(magic != value) {
        result = false;
    }
    if(!ignore) {
        stream.clear();
        stream.seekg(0, std::ios::beg);
    }
    return result;
}

Text GetSavegameFile() {
    const char *fileName = "game.bin";

    // Fetches the path of TEMP folder.
    Text target = GetLocalFolder();

    // Forms the file path.
    Append(target, fileName);

    return target;
}

bool SaveGame(const MatchInfo &match) {
    using namespace std;

    // Fetches the file name.
    Text target = GetSavegameFile();

    // Opens the file in the desired path.
    ofstream file(target._data, ios::out | ios::trunc | ios::binary);
    if(!file.is_open()) {
        return false;
    }

    // Destroys the target object
    Destroy(target);

    // Writes the whole match to the file.
    if(!WriteMatch(file, match).good()) {
        return false;
    }

    return true;
}

bool LoadGame(MatchInfo &match) {
    using namespace std;

    // Fetches the file name.
    Text target = GetSavegameFile();

    // Opens the file in the desired path.
    ifstream file(target._data, ios::in | ios::binary);
    if(!file.is_open()) {
        return false;
    }

    // Destroys the target object.
    Destroy(target);

    // Attempts to read the match from the file.
    if(!ReadMatch(file, match).good()) {
        return false;
    } 

    return true;
}

bool GameExists() {
    using namespace std;

    // Fetches the file name.
    Text target = GetSavegameFile();

    // Tries to open the file.
    ifstream file(target._data, ios::in | ios::binary);

    // Destroys the target object.
    Destroy(target);

    // Checks if the file exists.
    return file.is_open();
}