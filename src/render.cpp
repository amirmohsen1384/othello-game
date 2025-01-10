#include "../include/graphics.h"
#include "../include/game.h"
#include <iostream>
#include <cstring>
using namespace std;

#define EMPTY_COLOR Gray
#define PLAYER_COLOR BrightBlue
#define OPPONENT_COLOR BrightRed
#define VALID_COLOR BrightMagenta

void PrintGrid(const Table &table, Player *players, Piece turn) {
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
                letter = Uppercase(players[PLAYER_USER]._name._data[0]);

            } else {
                color = OPPONENT_COLOR;
                letter = Uppercase(players[PLAYER_OPPONENT]._name._data[0]);

            }

            SetForeground(color);
            cout << letter << '\t';
            ResetForeground();
        }
        cout << endl << endl;
    }
}

void PrintGame(const Table &table, Player *players, Piece turn) {
    // Ensure that the array containing players is not invalid.
    if(players == nullptr) {
        return;
    }
    
    // Print the information of player 1
    SetForeground(PLAYER_COLOR);

    Print(players[PLAYER_USER]._name);
    cout << endl << players[PLAYER_USER]._count << endl << endl;
    
    ResetForeground();

    // Print the information of player 2
    SetForeground(OPPONENT_COLOR);

    Print(players[PLAYER_OPPONENT]._name);
    cout << endl << players[PLAYER_OPPONENT]._count << endl;

    ResetForeground();

    // Print a seperator
    int spaces = table._width * 8;
    for(int i = 0; i < spaces; ++i) {
        cout << '=';
    }
    cout << endl << endl;

    // Print the game grid
    PrintGrid(table, players, turn);

    // Print a seperator
    for(int i = 0; i < spaces; ++i) {
        cout << '=';
    }
    cout << endl;
}