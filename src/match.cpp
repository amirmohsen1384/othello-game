#include <iostream>
#include "system.h"
#include "match.h"
#include <limits>

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
    cout << ':' << endl << "Please select your position (Enter -1 to save the game): ";

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
    else if(index == -1) {
        state = Normal;
    }
    else {
        state = IllegalPoint;
    }
    return index;
}

bool MatchContinues(MatchInfo &game) {
    bool result = true;
    Coordinates one = GetLegalPoints(game._environment, game._turn);
    if(IsEmpty(one)) {
        ToggleTurn(game._turn);
        Coordinates two = GetLegalPoints(game._environment, game._turn);
        if(IsEmpty(two)) {
            result = false;
        
        } else {
            result = true;
        }
        Destroy(two);
    
    } else {
        result = true;
    }
    Destroy(one);
    return result;
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

void NarrateResult(const MatchInfo &match) {
    using namespace std;

    // Resets the console.
    ClearConsole();

    // Tells everyone the point of each player.
    PrintWith(match._players[PLAYER_USER]._name, BrightBlue);
    cout << ": " << match._players[PLAYER_USER]._count << endl;

    PrintWith(match._players[PLAYER_OPPONENT]._name, BrightBlue);
    cout << ": " << match._players[PLAYER_OPPONENT]._count << endl;

    // Draws a seperator.
    for(int i = 1; i <= 20; i++) {
        cout << '=';
    }
    cout << endl;

    // Tells everyone the result.
    switch(match._status) {
        case UserWon: {
            PrintWith(match._players[PLAYER_USER]._name, BrightBlue);
            cout << ':' << ' ' << "You won the game. Congrats! ;)" << endl;
            break;
        }
        case OpponentWon: {
            PrintWith(match._players[PLAYER_OPPONENT]._name, BrightBlue);
            cout << ':' << ' ' << "You won the game. Congrats! ;)" << endl;
            break;
        }
        case GameDraw: {
            cout << "Ouch! Graw Draw. Nobody won. :|" << endl;
            break;
        }
    }
}

void CreateNewGame(MatchInfo &match) {
    using namespace std;
    match._environment = Create(6, 6);

    // Gets the names of players.
    InputPlayersName(match);
    ClearConsole();

    // Selects who goes first.
    match._turn = PLAYER_USER;

    // Initializes the state as undefined.
    match._status = Undefined;

    // Sets the points as two.
    match._players[PLAYER_USER]._count = 2;
    match._players[PLAYER_OPPONENT]._count = 2;

    // Welcome to the new game.
    PrintWith("Are you ready? Let's go! ;)", BrightYellow);
    Pause(1);
}

void PlayMatch(MatchInfo &match) {
    using namespace std;
    while(MatchContinues(match)) {
        ClearConsole();

        // Get the legal points for the current player.
        Coordinates legals = GetLegalPoints(match._environment, match._turn);
        InputState state = Normal;
        int result = 0;
        do {
            // Prints the current match.
            PrintMatch(match, legals);

            // Get an input from the user.
            result = GetMatchInput(cin, match, legals, state);
            ClearConsole();

            // Gets out of the loop if the input is valid.
            if(state == Normal) {
                break;
            }
        }
        while(true);

        // Decide based on the result
        if(result == -1) {
            // Saves the game and reports to the user.
            SaveGame(match);
            PrintWith("Saved successfully. :)", Green);

            // Holds for the user to press a key.
            cout << endl << "Press any key to exit." << endl;
            InputKey();

            Destroy(legals);
            exit(EXIT_SUCCESS);

        } else {
            PutPiece(match._environment, legals._data[result], match._turn);
            UpdatePlayersCount(match._environment, match._players);
            ToggleTurn(match._turn);

        }
        // Destroy the legal points.
        Destroy(legals);
    }
}