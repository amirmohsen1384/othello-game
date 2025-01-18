#include <iostream>
#include "system.h"
#include "match.h"
#include "game.h"

using namespace std;

const Color emptyColor = Gray;
const Color userColor = BrightBlue;
const Color opponentColor = BrightRed;
const Color validColor = BrightMagenta;

void PrintGrid(const MatchInfo &match, const Coordinates &legals) {
    // Fetches required information from the match
    const TurnInfo &turn = match._turn;
    const Table &table = match._environment;
    const Player &user = match._players[PLAYER_USER];
    const Player &opponent = match._players[PLAYER_OPPONENT];

    // Prints the environment in a user-friendly way.
    for(int j = 0; j < table._height; ++j) {
        for(int i = 0; i < table._width; ++i) {
            const Point point = {i, j};
            Cell *value = PointAt(table, point);

            if(*value < 0) {
                int index = Find(legals, point);
                if(index != NOT_FOUND) {
                    SetForeground(validColor);
                    cout << '\b' << '(' << index + 1 << ')';

                } else {
                    SetForeground(emptyColor);
                    cout << 'O';

                } 

            } else if(*value == PLAYER_USER) {
                SetForeground(userColor);
                cout << Uppercase(user._name._data[0]);

            } else {
                SetForeground(opponentColor);
                cout << Uppercase(opponent._name._data[0]);
            }

            cout << '\t';
            ResetForeground();
        }
        cout << endl << endl;
    }
}

void PrintMatch(const MatchInfo &match, const Coordinates &legals) {
    // Fetch the information about players
    const Player &user = match._players[PLAYER_USER];
    const Player &opponent = match._players[PLAYER_OPPONENT];

    // Print the information of player 1
    SetForeground(userColor);

    Print(user._name);
    cout << endl << user._count << endl << endl;
    
    ResetForeground();

    // Print the information of player 2
    SetForeground(opponentColor);
    
    Print(opponent._name);
    cout << endl << opponent._count << endl;

    ResetForeground();

    // Fetch the information about the table
    const Table &table = match._environment;

    // Print a seperator
    int spaces = table._width * 8;
    for(int i = 0; i < spaces; ++i) {
        cout << '=';
    }
    cout << endl << endl;

    // Print the game grid
    PrintGrid(match, legals);

    // Print a seperator
    for(int i = 0; i < spaces; ++i) {
        cout << '=';
    }
    cout << endl;
}