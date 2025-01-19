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

// Launches a game and starts it.
void LaunchMatch(MatchInfo &match) {
    if(GameExists()) {
        if(RequestToLoad()) {
            LoadGame(match);
            return;
        }
    }
    CreateNewGame(match);
}