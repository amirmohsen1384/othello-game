#include "../include/game.h"
#include "../include/misc.h"
#include <iostream>
using namespace std;

void PrintGrid(const Table &table, Player *players, const Point &initial, int scaleX, int scaleY) {
    for(int i = 0; i < table._width; ++i) {
        for(int j = 0; j < table._height; ++j) {
            // Retrieve the required information
            Cell *value = PointAt(table, {i, j});
            Point pos = {i * scaleX, j * scaleY};

            // Translate the initial point
            pos = Add(pos, initial);

            // Convert the data into a user-friendly character
            char letter = '\0';
            if(*value < 0) {
                letter = 'O';

            } else if(*value == PLAYER_USER) {
                letter = players[PLAYER_USER]._name._data[0];

            } else {
                letter = players[PLAYER_OPPONENT]._name._data[0];
            }

            // Render the character
            GoToLocation(pos);
            cout << letter;
        }
    }
}

void PrintGame(const Table &table, Player *players) {
    // Ensure that the array containing players is not invalid.
    if(players == nullptr) {
        return;
    }
    
    // Defined some constants to render the contents.
    const int gap = 24;
    const int length = players[PLAYER_USER]._name._size + gap + players[PLAYER_OPPONENT]._name._size;

    // Print the information of player 1
    Print(players[PLAYER_USER]._name);
    GoToLocation({0, 1});

    cout << "Count: " << players[PLAYER_USER]._count;
    GoToLocation({players[PLAYER_USER]._name._size + gap, 0});

    // Print the information of player 2
    Print(players[PLAYER_OPPONENT]._name);

    GoToLocation({players[PLAYER_USER]._name._size + gap, 1});
    cout << "Count: " << players[PLAYER_OPPONENT]._count;

    // Print a seperator
    cout << endl;
    for(int i = 0; i < length; ++i) {
        cout << '=';
    }

    // Print the table
    const int scaleX = 7, scaleY = 4;

    int margin = (length - scaleX * (table._width - 1)) / 2;
    Point start = {margin, 4};

    PrintGrid(table, players, start, scaleX, scaleY);
    cout << endl;

    // Print a seperator
    cout << endl;
    for(int i = 0; i < length; ++i) {
        cout << '=';
    }

    cout << endl;
}