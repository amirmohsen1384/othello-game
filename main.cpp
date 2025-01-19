#include <iostream>
#include "src/commands.h"

int main() {
    using namespace std;

    MatchInfo info;
    InitializeMatch(info);
    
    StartGame(info);

    return EXIT_SUCCESS;
}
