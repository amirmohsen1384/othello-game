#include <iostream>
#include "system.h"
#include "game.h"

void Destroy(Player &player) {
    Destroy(player._name);
    player._count = 0;
}

MatchInfo* Define(int width, int height, const TurnInfo &initial) {
    MatchInfo* game = new MatchInfo;

    game->_environment = Create(width, height);
    game->_status = Undefined;
    game->_error = NoError;
    game->_turn = initial;

    Player *user = &game->_players[PLAYER_USER];
    Player *opponent = &game->_players[PLAYER_OPPONENT];
    
    user->_name._data = opponent->_name._data = nullptr;
    user->_name._size = opponent->_name._size = 0;
    user->_count = opponent->_count = 2;
    
    return game;
}

MatchInfo* Define(int width, int height, const Text &playerName, const Text &opponentName, const TurnInfo &initial)
{
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

void Delete(MatchInfo *game)
{
    if(game == nullptr) {
        Destroy(game->_environment);
        delete game;
        game = nullptr;
    }
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
    // Fetch the required resources.
    const Color userColor = BrightGreen;
    const Color opponentColor = BrightMagenta;
    Player &user = match._players[PLAYER_USER];
    Player &opponent = match._players[PLAYER_OPPONENT];

    // Input the user's name.
    PrintWith("Enter the name of the first player: ", userColor);
    Text userName = GetLine();
    ClearConsole();

    // Input the opponent's name.
    PrintWith("Enter the name of the second player: ", opponentColor);
    Text opponentName = GetLine();
    ClearConsole();

    user._name = userName;
    opponent._name = opponentName;
}

void FetchFromPlayer(MatchInfo &match) {
    Player &current = match._players[match._turn];
    switch(match._error) {
        case IllegalPoint: {
            const Color error = Red;
            PrintWith("You have entered an invalid point!\n", error);
            break;
        }
        case BadInput: {
            const Color error = Red;
            PrintWith("You have entered someting invalid!\n", error);
            break;
        }
    }
}

void Advance(MatchInfo &match) {
    // Creates a reference for the player.
    Player &current = match._players[match._turn];

    // Prints the whole match.
    PrintMatch(match);

    // Fetch something from the player.
    do {
        FetchFromPlayer(match);

    } while(match._error != NoError);
}