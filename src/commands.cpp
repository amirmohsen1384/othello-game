#include "commands.h"
#include <iostream>
#include "system.h"
#include <limits>

void Track(const char *msg) {
    using namespace std;
    cout << msg << endl;
    Pause(1);
}

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

    // Deletes any existing match from the computer.
    Text path = GetSavegameFile();
    RemoveFile(path);
    Destroy(path);

    // Gets the dimensions of the table.
    {
        ChoiceList choices;
        Initialize(choices);

        Text small = Create("6 x 6");
        Append(choices, small);

        Text medium = Create("8 x 8");
        Append(choices, medium);

        Text large = Create("10 x 10");
        Append(choices, large);

        const char *descripion = "Please select the dimensions of the match.";
        int result = Execute(choices, descripion);

        Track("Track 11: We got a choice so far. We've got a list in the memory.");
        ClearConsole();

        Destroy(choices);
        Track("Track 12: Destroyed the choice.");

        switch(result) {
            case 0: {
                match._environment = Create(6, 6);
                break;
            }
            case 1: {
                match._environment = Create(8, 8);
                break;
            }
            case 2: {
                match._environment = Create(10, 10);
                break;
            }
        }
    }

    // Gets the names of players.
    InputPlayersName(match);
    ClearConsole();

    // Selects who goes first.
    {
        ChoiceList choices;
        Initialize(choices);

        Text user = Create(match._players[PLAYER_USER]._name._data);
        Append(user, " goes first");
        Append(choices, user);

        Text opponent = Create(match._players[PLAYER_OPPONENT]._name._data);
        Append(opponent, " goes first");
        Append(choices, opponent);

        TurnInfo result = Execute(choices, "Who wants to go first in this match?");
        match._turn = result;
        ClearConsole();

        Destroy(choices);
    }

    // Initializes the state as undefined.
    match._status = Undefined;

    // Sets the points as two.
    match._players[PLAYER_USER]._count = 2;
    match._players[PLAYER_OPPONENT]._count = 2;

    // Welcome to the new game.
    PrintWith("Are you players ready? Let's go! ;)", BrightYellow);
    Pause(1);

    ClearConsole();
}

void StartGame(MatchInfo &match) {
    using namespace std;

    // Loads the existing match from the last time.
    if(GameExists()) {
        if(RequestToLoad()) {
            Track("Track 4: Exists, Accepted - About to load the game.");
            if(!LoadGame(match)) {
                cout << "Sorry. We couldn't load the game!" << endl;
                Pause(2);
                CreateNewGame(match);
            }
        } else {
            Track("Track 4: Exist, Declined - Creating a new game.");
            CreateNewGame(match);
        }
    
    } else {
        Track("Track 3: Not exist - Creating a new game");
        CreateNewGame(match);
    }

    // Starts the current game.
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
            result = GetMatchInput(match, legals, state);
            ClearConsole();

            // Gets out of the loop if the input is valid.
            if(state == Normal) {
                break;
            }
        }
        while(true);

        // Decide based on the result
        if(result == -1) {
            SaveGame(match);
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