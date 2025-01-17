#include "commands.h"
#include "system.h"
#include "match.h"
#include <iostream>
#include <limits>

bool AskPermission(const char *message) {
    using namespace std;
    char answer = '\0';

    while(true) {
        // Prints the message
        cout << message << endl;
        cout << "Y) Yes" << '\t' << "N) No" << endl;

        // Asks the user to select a choice.
        istream &stream = (cin >> answer);
        if(stream.bad()) {
            stream.ignore(numeric_limits<streamsize>::max(), '\n');
            stream.clear();

            ClearConsole();
            cerr << "You have entered an invalid input.\n" << endl;
            continue;
        }

        // Force the user to select only between Yes or No.
        switch(answer) {
            case 'Y': {
                return true;
            }
            case 'N': {
                return false;
            }
            default: {
                ClearConsole();
                cerr << "You have entered an invalid input.\n" << endl;
                continue;
            }
        }
    }
}

void CreateNewGame(MatchInfo &match) {
    using namespace std;

    // Clears the console.
    ClearConsole();

    // Gets the players' names.
    InputPlayersName(match);

    // Asks the user about the dimension of the game.
    int result = 0;

    while(true) {
        cout << "Select the dimension of the game:" << endl;
        cout << '1' << ')' << ' ' << "6 x 6" << endl;
        cout << '2' << ')' << ' ' << "8 x 8" << endl;
        cout << '3' << ')' << ' ' << "10 x 10" << endl;
        istream &stream = (cin >> result);
        if(stream.fail()) {
            ClearConsole();
            stream.clear();
            stream.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You have entered an invalid value." << endl << endl;
            continue;
        }
        else if(result >= 1 && result <= 3) {
            break;
        }
        else {
            ClearConsole();
            cout << "The entered choice is not avaliable" << endl << endl;
            continue;
        }
    }

    switch(result) {
        case 1: {
            match._environment = Create(6, 6);
            break;
        }
        case 2: {
            match._environment = Create(8, 8);
            break;
        }
        case 3: {
            match._environment = Create(10, 10);
            break;
        }
    }
}

void StartGame(MatchInfo &match) {
    using namespace std;

    // Initializes the current match.
    if(GameExists()) {
        const char *message = "You have a saved game in your history.\nWould you like to continue?";
        if(AskPermission(message)) {
            cerr << "four" << endl;
            if(!LoadGame(match)) {
                CreateNewGame(match);
            }

        } else {
            CreateNewGame(match);
        }

    } else {
        CreateNewGame(match);
    }

    // Starts the current game.
    while(MatchContinues(match)) {
        ClearConsole();

        // Get the legal points for the current player.
        Coordinates legals = GetLegalPoints(match._environment, match._turn);

        // Prints the current match.
        PrintMatch(match, legals);

        // Get an input from the user.
        int result = 0;
        InputState state = Normal;
        do {
            result = GetMatchInput(match, legals, state);
            if(state == Normal) {
                break;
            }
        }
        while(true);

        // Decide based on the result
        if(result == -1) {
            SaveGame(match);
            return;
        }
        else {
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

    // Remove the savegame
    remove(GetSavegameFile()._data);

    // Holds for the user to press a key.
    cout << "Press any key to continue." << endl;
    InputKey();
}