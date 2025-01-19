#include "commands.h"
#include <iostream>
#include "system.h"
#include <limits>

// Asks for permission
bool RequestToLoad() {
    ChoiceList choices;

    Text reject = Create("No. Start a new game.");
    Append(choices, reject);

    Text accept = Create("Yes! I want to continue.");
    Append(choices, accept);

    const char *description = "You have an unfinished match from the last time.\nWould you like to do?";
    int result = Execute(choices, description);
    ClearConsole();

    Destroy(choices);
    return result;
} 

// Starts a new game
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

void StartGame(MatchInfo &match) {
    using namespace std;

    LoadGame(match);

    // Starts the game.
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
            ClearConsole();
            PrintWith("The game has been saved. See you later! :)", Green);

            // Holds for the user to press a key.
            cout << endl << "Press any key to continue." << endl;
            Destroy(legals);
            InputKey();
            return;

        } else {
            PutPiece(match._environment, legals._data[result], match._turn);
            UpdatePlayersCount(match._environment, match._players);
            ToggleTurn(match._turn);

        }
        // Destroy the legal points.
        Destroy(legals);
    }

    // Evaluates the result.
    EvaluateResult(match);
    ClearConsole();

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

    // Holds for the user to press a key.
    cout << "Press any key to continue." << endl;
    InputKey();
}