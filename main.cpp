#include <iostream>
#include "include/game.h"
#include "include/system.h"

int main() {
    using namespace std;

    Match match = Define(6, 6, PLAYER_USER);
    Execute(match);

    PrintWith("Game Finished!", Green);
    Pause(1);

    if(match->_status == UserWon) {
        PrintWith(match->_players[PLAYER_USER]._name, PLAYER_COLOR);
        cout << ':' << ' ' << "Congratulations. You won the game!" << endl;
    }
    else if(match->_status == OpponentWon) {
        PrintWith(match->_players[PLAYER_OPPONENT]._name, OPPONENT_COLOR);
        cout << ':' << ' ' << "Congratulations. You won the game!" << endl;
    }
    else if(match->_status == GameDraw) {
        cout << "Game Draw." << endl;
 
    }
    
    cout << '\n' << "Press any key to exit the game...";
    InputKey();
    
    return EXIT_SUCCESS;
}
