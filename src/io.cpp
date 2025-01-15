#include "../include/system.h"
#include "../include/game.h"
#include <fstream>

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

    // Destroy the existing table
    Destroy(table);

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
    stream.write(reinterpret_cast<const char*>(&text._size), sizeof(Size));
    stream.write(text._data, (text._size + 1) * sizeof(char));
    return stream;
}

std::ifstream& ReadText(std::ifstream &stream, Text &text) {
    using namespace std;

    // Destroys any existing text.
    Destroy(text);

    // Reads the length of the text
    stream.read(reinterpret_cast<char*>(&text._size), sizeof(Size));

    // Reserves the required memory.
    text._data = static_cast<char*>(realloc(text._data, sizeof(char) * (text._size + 1)));
    if(text._data == NULL) {
        return stream;
    }

    // Reads the text from the stream.
    stream.read(text._data, (text._size + 1) * sizeof(char));

    // Checks if reading is successful.
    Size bytes = stream.gcount();
    if(bytes != (text._size + 1)) {
        Destroy(text);
    }

    return stream;
}

std::ofstream& WritePlayer(std::ofstream &stream, const Player &data) {
    using namespace std;
    stream.write(reinterpret_cast<const char*>(&data._count), sizeof(Size));
    WriteText(stream, data._name);
    return stream;
}

std::ifstream& ReadPlayer(std::ifstream &stream, Player &data) {
    using namespace std;

    // Delete any existing data in the player
    Destroy(data);

    // Read new pieces of data
    stream.read(reinterpret_cast<char*>(&data._count), sizeof(Size));
    ReadText(stream, data._name);

    return stream;
}

std::ofstream& WriteMatch(std::ofstream &stream, const MatchInfo &match) {
    const Size magic = 0xD3314D;
    // Write the magic number to the stream
    stream.write(reinterpret_cast<const char*>(&magic), sizeof(Size));

    // Write the user to the stream
    WritePlayer(stream, match._players[PLAYER_USER]);

    // Write the opponent to the stream
    WritePlayer(stream, match._players[PLAYER_OPPONENT]);

    // Write the turn to the stream
    stream.write(reinterpret_cast<const char*>(match._turn), sizeof(bool));

    // Write the current state of the match to the stream
    stream.write(reinterpret_cast<const char*>(match._status), sizeof(Size));

    // Write the whole table to the stream
    WriteTable(stream, match._environment);

    return stream;
}

std::ifstream& ReadMatch(std::ifstream &stream, MatchInfo &match) {
    const Size magic = 0xD3314D;
    // Read the magic number from the stream
    Size value = 0;
    stream.read(reinterpret_cast<char*>(&value), sizeof(Size));
    if(magic != value) {
        return stream;
    }

    // Delete any existing data from the match
    Delete(&match);

    // Read the user from the stream
    ReadPlayer(stream, match._players[PLAYER_USER]);

    // Read the opponent from the stream
    ReadPlayer(stream, match._players[PLAYER_OPPONENT]);

    // Read the turn from the stream
    stream.read(reinterpret_cast<char*>(match._turn), sizeof(bool));

    // Read the current state of the match from the stream
    stream.read(reinterpret_cast<char*>(match._status), sizeof(Size));

    // Read the whole table from the stream
    ReadTable(stream, match._environment);

    return stream;
}

bool SaveMatch(const MatchInfo &match) {
    using namespace std;
    
    // Get the path of TEMP folder
    Text folder = GetTempFolder();

    Destroy(folder);
}