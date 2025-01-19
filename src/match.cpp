#include <iostream>
#include "system.h"
#include "match.h"
#include <limits>

MatchInfo* Define(int width, int height, const TurnInfo &initial) {
    MatchInfo* game = new MatchInfo;

    game->_environment = Create(width, height);
    game->_status = Undefined;
    game->_turn = initial;

    Player *user = &game->_players[PLAYER_USER];
    Player *opponent = &game->_players[PLAYER_OPPONENT];
    
    user->_name._data = opponent->_name._data = nullptr;
    user->_name._size = opponent->_name._size = 0;
    user->_count = opponent->_count = 2;
    
    return game;
}

MatchInfo* Define(int width, int height, const Text &playerName, const Text &opponentName, const TurnInfo &initial) {
    MatchInfo *game = Define(width, height, initial);
    if(game == nullptr) {
        return nullptr;
    }
    
    Player *user = &game->_players[PLAYER_USER];
    Player *opponent = &game->_players[PLAYER_OPPONENT];

    user->_name = playerName;
    opponent->_name = opponentName;
    
    return game;
}

void Delete(MatchInfo &game) {
    Destroy(game._environment);
    Destroy(game._players[PLAYER_USER]._name);
    Destroy(game._players[PLAYER_OPPONENT]._name);
}

void EvaluateResult(MatchInfo &match) {
    const int user = match._players[PLAYER_USER]._count;
    const int opponent = match._players[PLAYER_OPPONENT]._count;
    if(user == opponent) {
        match._status = GameDraw;
    }
    else if(user > opponent) {
        match._status = UserWon;
    }
    else {
        match._status = OpponentWon;
    }
}

void InputPlayersName(MatchInfo &match) {
    // Input the user's name.
    PrintWith("Enter the name of player 1: ", BrightGreen);
    match._players[PLAYER_USER]._name = GetLine();
    ClearConsole();

    // Input the opponent's name.
    PrintWith("Enter the name of player 2: ", BrightMagenta);
    match._players[PLAYER_OPPONENT]._name = GetLine();
    ClearConsole();
}

int GetMatchInput(std::istream &stream, MatchInfo &match, const Coordinates &legals, InputState &state) {
    using namespace std;

    // Print a relevant error message if any.
    const Color error = Red;
    switch(state) {
        case IllegalPoint: {
            PrintWith("You have entered an invalid point!\n", error);
            break;
        }
        case BadInput: {
            PrintWith("You have entered someting invalid!\n", error);
            break;
        }
    }

    // Ask the current player to enter something.
    int index = 0;
    PrintWith(match._players[match._turn]._name, BrightYellow);
    cout << ':' << endl << "Please select your position: ";

    // Get a value from the input
    stream >> index;
    
    // Handle bad input
    if(stream.fail()) {
        stream.clear();
        state = BadInput;
        stream.ignore(numeric_limits<streamsize>::max(), '\n');
        return legals._size;
    }
    
    // Process the entered input.
    if(index >= 1 && index <= legals._size) {
        state = Normal;
        index--;
    }
    else {
        state = IllegalPoint;
    }
    return index;
}

bool MatchContinues(MatchInfo &game) {
    Coordinates one = GetLegalPoints(game._environment, game._turn);
    if(IsEmpty(one)) {
        ToggleTurn(game._turn);
        Coordinates two = GetLegalPoints(game._environment, game._turn);
        if(IsEmpty(two)) {
            Destroy(one);
            Destroy(two);
            return false;
        
        } else {
            Destroy(one);
            Destroy(two);
            return true;
        }
    }
    Destroy(one);
    return true;
}

void InitializeMatch(MatchInfo &match) {
    match._environment._data = nullptr;
    match._environment._height = match._environment._width = 0;

    Player &user = match._players[PLAYER_USER];
    Player &opponent = match._players[PLAYER_OPPONENT];

    user._name._data = opponent._name._data = nullptr;
    user._name._size = opponent._name._size = 0;
    user._count = opponent._count = 2;

    match._status = Undefined;
    match._turn = PLAYER_USER;
}

void InitializeMatch(MatchInfo &match, int width, int height, const TurnInfo &init) {
    InitializeMatch(match);
    match._environment = Create(width, height);
    match._turn = init;
}

void InitializeMatch(MatchInfo &match, int width, int height, const Text &userName, const Text &opponentName, const TurnInfo &init) {
    InitializeMatch(match, width, height, init);
    match._players[PLAYER_USER]._name = userName;
    match._players[PLAYER_OPPONENT]._name = opponentName;
}