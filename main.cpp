#include <iostream>
#include "src/match.h"
#include "src/system.h"

int main() {
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
    ClearConsole();

    return EXIT_SUCCESS;
}