#include <iostream>
#include "src/match.h"
#include "src/system.h"
#include "src/scoreboard.h"

// Deals with playing a match.
void LoadReversi() {
    using namespace std;
    ClearConsole();

    // Defines a match and initializes it.
    MatchInfo match;
    InitializeMatch(match);

    // Launches a game and starts it.
    LaunchMatch(match);
    ClearConsole();

    // Gives the match a play.
    PlayMatch(match);
    ClearConsole();

    // Evaluates the reuslt.
    EvaluateResult(match);
    ClearConsole();

    // Narrates the result.
    NarrateResult(match);

    // Loads the scoreboard.
    Scoreboard board;
    Initialize(board);
    LoadScoreboard(board);

    // Calculates the area of the table.
    const Dimension area = match._environment._width * match._environment._height;

    // Finds the ranked player.
    switch(match._status) {
        case OpponentWon: {
            RankedPlayer target;
            Initialize(target, match._players[PLAYER_OPPONENT], area);
            AddRankedPlayer(board, target);
            break;
        }
        case UserWon: {
            RankedPlayer target;
            Initialize(target, match._players[PLAYER_USER], area);
            AddRankedPlayer(board, target);
            break;
        }
    }

    // Saves the scoreboard
    SaveScoreboard(board);

    // Removes the history after finishing the match.
    RemoveFile(GetSavegameFile());
    Delete(match);

    // Waits for the user to press a key.
    cout << endl << "Press any key to get back to the main menu..." << endl;
    InputKey();
}

void ShowScoreboard() {
    using namespace std;
    ClearConsole();

    // Loads the scoreboard.
    Scoreboard board;
    Initialize(board);
    LoadScoreboard(board);

    // Shows the scoreboard.
    PrintScoreboard(board);

    // Waits for the user to press a key.
    cout << "Press any key to get back to the main menu..." << endl;
    InputKey();
}

int main() {
    using namespace std;

    ShowScoreboard();

    return EXIT_SUCCESS;
}