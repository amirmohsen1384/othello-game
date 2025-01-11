#include "../include/system.h"
#include "../include/game.h"
#include <iostream>
#include <cstring>
using namespace std;

void PrintGrid(const Match match) {
    const TurnInfo &turn = match->_turn;
    const Table &table = match->_environment;
    const Player &user = match->_players[PLAYER_USER];
    const Player &opponent = match->_players[PLAYER_OPPONENT];
    for(int j = 0; j < table._height; ++j) {
        for(int i = 0; i < table._width; ++i) {
            Cell *value = PointAt(table, {i, j});
            Color color = Black;
            char letter = '\0';

            if(*value < 0) {
                letter = 'O';
                color = IsLegal(table, turn, {i, j}) ? VALID_COLOR : EMPTY_COLOR;

            } else if(*value == PLAYER_USER) {
                color = PLAYER_COLOR;
                letter = Uppercase(user._name._data[0]);

            } else {
                color = OPPONENT_COLOR;
                letter = Uppercase(opponent._name._data[0]);

            }

            SetForeground(color);
            cout << letter << '\t';
            ResetForeground();
        }
        cout << endl << endl;
    }
}

void PrintMatch(const Match &match) {
    // Ensure that the array containing players is not invalid.
    if(&match == nullptr) {
        return;
    }
    
    // Fetch the information about players
    Player &user = match->_players[PLAYER_USER];
    Player &opponent = match->_players[PLAYER_OPPONENT];

    // Print the information of player 1
    SetForeground(PLAYER_COLOR);

    Print(user._name);
    cout << endl << user._count << endl << endl;
    
    ResetForeground();

    // Print the information of player 2
    SetForeground(OPPONENT_COLOR);

    Print(opponent._name);
    cout << endl << opponent._count << endl;

    ResetForeground();

    // Fetch the information about the table
    Table &table = match->_environment;

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