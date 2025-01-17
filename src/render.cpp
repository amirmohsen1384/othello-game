#include <iostream>
#include "system.h"
#include "match.h"
#include "game.h"

using namespace std;

const Color emptyColor = Gray;
const Color userColor = BrightBlue;
const Color opponentColor = BrightRed;
const Color validColor = BrightMagenta;

void PrintGrid(const MatchInfo &match) {
    // Fetches required information from the match
    const TurnInfo &turn = match._turn;
    const Table &table = match._environment;
    const Player &user = match._players[PLAYER_USER];
    const Player &opponent = match._players[PLAYER_OPPONENT];

    // Prints the environment in a user-friendly way.
    for(int j = 0; j < table._height; ++j) {
        for(int i = 0; i < table._width; ++i) {
            Cell *value = PointAt(table, {i, j});
            Color color = Black;
            char letter = '\0';

            if(*value < 0) {
                letter = 'O';
                color = IsLegal(table, turn, {i, j}) ? validColor : emptyColor;

            } else if(*value == PLAYER_USER) {
                color = userColor;
                letter = Uppercase(user._name._data[0]);

            } else {
                color = opponentColor;
                letter = Uppercase(opponent._name._data[0]);

            }

            SetForeground(color);
            cout << letter << '\t';
            ResetForeground();
        }
        cout << endl << endl;
    }
}

void PrintMatch(const MatchInfo &match) {
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
    PrintGrid(match);

    // Print a seperator
    for(int i = 0; i < spaces; ++i) {
        cout << '=';
    }
    cout << endl;
}