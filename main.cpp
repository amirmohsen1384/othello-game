#include <iostream>
#include "src/commands.h"

int main() {
    using namespace std;

    MatchInfo info;
    InitializeMatch(info);
    
    StartGame(info);

    Delete(info);

    return EXIT_SUCCESS;
}
