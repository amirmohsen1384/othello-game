#include <iostream>
#include "src/commands.h"

int main() {
    using namespace std;

    MatchInfo match;
    InitializeMatch(match);
    
    StartGame(match);

    return EXIT_SUCCESS;
}
