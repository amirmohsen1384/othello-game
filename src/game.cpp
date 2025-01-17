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

void Execute(MatchInfo &game) {
    using namespace std;

    // Creates some references to the players.
    Player &user = game._players[PLAYER_USER];
    Player &opponent = game._players[PLAYER_OPPONENT];

    // Clears the whole screen.
    ClearConsole();

    // Get the name of players.
    

    if(IsEmpty(user._name) || IsEmpty(opponent._name)) {
        PrintWith("Enter the name of player 1: ", BrightCyan);
        Text userName = GetLine();
        ClearConsole();

        PrintWith("Enter the name of player 2: ", BrightGreen);
        Text opponentName = GetLine();
        ClearConsole();

        user._name = userName;
        opponent._name = opponentName;
    }

    do {
        // Creates a reference to the current player
        Player &current = (game._turn == PLAYER_USER) ? user : opponent;
        
        // Prints the whole match
        PrintMatch(game);

        // Asks to select a position
        if(game._status == IllegalPoint) {
            PrintWith("You have entered an invalid point.\n", Red);
        }
        PrintWith(current._name, (game._turn == PLAYER_USER) ? PLAYER_COLOR : OPPONENT_COLOR);
        cout << ':' << '\n' << ' ' << "Please select a place in the table: ";

        Point temp;
        GetPoint(temp);

        // Checks if the entered point is legal
        if(!IsLegal(game._environment, game._turn, temp)) {
            game._status = IllegalPoint;

        } else {
            PutPiece(game._environment, temp, game._turn);
            UpdatePlayersCount(game._environment, game._players);
            game._status = Undefined;

        }
        ClearConsole();
    }
    while(MatchContinues(game));

    if(user._count > opponent._count) {
        game._status = UserWon;
    }

    else if(user._count == opponent._count) {
        game._status = GameDraw;
    }

    else {
        game._status = OpponentWon;

    }
}