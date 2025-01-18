#include "system.h"
#include <fstream>
#include "match.h"
#include "game.h"


std::ofstream& WriteTable(std::ofstream &stream, const Table &table) {
    using namespace std;

    // Write the dimensions of the table
    stream.write(reinterpret_cast<const char*>(&table._width), sizeof(Dimension));
    stream.write(reinterpret_cast<const char*>(&table._height), sizeof(Dimension));

    // Write the whole table
    stream.write(reinterpret_cast<const char*>(table._data), (table._width * table._height) * sizeof(Cell));

    return stream;
}

std::ifstream& ReadTable(std::ifstream &stream, Table &table) {
    using namespace std;

    // Read the dimensions of the table from the stream
    stream.read(reinterpret_cast<char*>(&table._width), sizeof(Dimension));
    stream.read(reinterpret_cast<char*>(&table._height), sizeof(Dimension));

    // Create a table with the read dimensions.
    table._data = static_cast<Cell*>(calloc(table._width * table._height, sizeof(Cell)));
    if(table._data == NULL) {
        return stream;
    }

    // Read the whole table from the stream.
    stream.read(reinterpret_cast<char*>(table._data), table._width * table._height * sizeof(Cell));
    return stream;
}

std::ofstream& WriteText(std::ofstream &stream, const Text &text) {
    using namespace std;
    if(!stream.write(reinterpret_cast<const char*>(&text._size), sizeof(Size)).good()) {
        return stream;
    }
    if(!stream.write(text._data, text._size * sizeof(char)).good()) {
        return stream;
    }
    return stream;
}

std::ifstream& ReadText(std::ifstream &stream, Text &text) {
    using namespace std;

    // Reads the length of the text
    if(!stream.read(reinterpret_cast<char*>(&text._size), sizeof(Size)).good()) {
        return stream;
    }

    // Reserves the required memory.
    text._data = static_cast<char*>(calloc(text._size + 1, sizeof(char)));
    if(text._data == NULL) {
        return stream;
    }

    // Reads the text from the stream.
    if(stream.read(text._data, text._size * sizeof(char)).good()) {
        return stream;
    }

    text._data[text._size] = '\0';

    return stream;
}

std::ofstream& WritePlayer(std::ofstream &stream, const Player &data) {
    using namespace std;
    if(!stream.write(reinterpret_cast<const char*>(&data._count), sizeof(Size)).good()) {
        return stream;
    }
    if(!WriteText(stream, data._name).good()) {
        return stream;
    }
    return stream;
}

std::ifstream& ReadPlayer(std::ifstream &stream, Player &data) {
    using namespace std;
    stream.read(reinterpret_cast<char*>(&data._count), sizeof(Size));
    ReadText(stream, data._name);
    return stream;
}

std::ofstream& WriteMatch(std::ofstream &stream, const MatchInfo &match) {
    using namespace std;

    // Write the user to the stream
    if(!WritePlayer(stream, match._players[PLAYER_USER]).good()) {
        return stream;
    }

    // Write the opponent to the stream
    if(!WritePlayer(stream, match._players[PLAYER_OPPONENT]).good()) {
        return stream;
    }

    // Write the turn to the stream
    if(!stream.write(reinterpret_cast<const char*>(&match._turn), sizeof(TurnInfo)).good()) {
        return stream;
    }

    // Write the current state of the match to the stream
    if(!stream.write(reinterpret_cast<const char*>(&match._status), sizeof(Size)).good()) {
        return stream;
    }

    // Write the whole table to the stream
    if(!WriteTable(stream, match._environment).good()) {
        return stream;
    }

    return stream;
}

std::ifstream& ReadMatch(std::ifstream &stream, MatchInfo &match) {
    using namespace std;

    // Read the user from the stream
    if(!ReadPlayer(stream, match._players[PLAYER_USER]).good()) {
        return stream;
    }

    // Read the opponent from the stream
    if(!ReadPlayer(stream, match._players[PLAYER_OPPONENT]).good()) {
        return stream;
    }

    // Read the turn from the stream
    if(!stream.read(reinterpret_cast<char*>(&match._turn), sizeof(TurnInfo)).good()) {
        return stream;
    }

    // Read the current state of the match from the stream
    if(!stream.read(reinterpret_cast<char*>(&match._status), sizeof(Size)).good()) {
        return stream;
    }

    // Read the whole table from the stream
    if(!ReadTable(stream, match._environment).good()) {
        return stream;
    }

    return stream;
}

const Size magic = 0xD3314D;

Text GetSavegameFile() {
    const char *fileName = "game.bin";

    // Fetches the path of TEMP folder.
    Text target = GetTempFolder();

    // Forms the file path.
    Append(target, fileName);

    return target;
}

bool SaveGame(const MatchInfo &match) {
    using namespace std;

    // Fetches the file name.
    Text target = GetSavegameFile();

    // Opens the file in the desired path.
    ofstream file(target._data, ios::out | ios::trunc);
    if(!file.is_open()) {
        return false;
    }
    
    // Writes the magic number to the file
    if(!file.write(reinterpret_cast<const char*>(&magic), sizeof(Size)).good()) {
        return false;
    }

    // Writes the whole match to the file.
    if(!WriteMatch(file, match).good()) {
        return false;
    }

    // Destroys the target object
    Destroy(target);

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

    // Read the magic number from the stream
    Size value = 0;
    if(!file.read(reinterpret_cast<char*>(&value), sizeof(Size)).good()) {
        return false;
    }
    else if(magic != value) {
        return false;
    }

    // Attempts to read the match from the file.
    if(!ReadMatch(file, match).good()) {
        return false;
    } 

    // Destroys the target object.
    Destroy(target);

    return true;
}

bool GameExists() {
    using namespace std;

    // Fetches the file name.
    Text target = GetSavegameFile();

    // Tries to open the file.
    ifstream file(target._data);
    file.open(target._data, ios::in | ios::binary);

    // Destroys the target object.
    Destroy(target);

    // Checks if the very first number is the magic number.
    if(!file.is_open()) {
        return false;

    } else {
        Size value = 0;
        if(!file.read(reinterpret_cast<char*>(&value), sizeof(Size)).good()) {
            return false;
        }
        else if(magic != value) {
            return false;
        }
        else {
            return true;
        }
    }
}