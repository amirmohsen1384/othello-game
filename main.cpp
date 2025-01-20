#include <iostream>
#include "src/match.h"
#include "src/system.h"
#include "src/scoreboard.h"

// Deals with playing a match.
void LoadReversi() {
    using namespace std;

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

    // Removes the history after finishing the match.
    RemoveFile(GetSavegameFile());
    Delete(match);

    // Waits for the user to press a key.
    cout << endl << "Press any key to exit..." << endl;
    InputKey();
}

int main() {
    using namespace std;

    LoadReversi();

    return EXIT_SUCCESS;
}