#include "scoreboard.h"
#include "system.h"
#include <cstring>

void Initialize(RankedPlayer &player) {
    player._ratio = 0;
    Initialize(player._player);
}

void Initialize(RankedPlayer &player, const Player &target, Dimension area) {
    // Converts to the type of a fill ratio.
    FillRatio points = target._count;
    FillRatio total = area;

    // Calculates the fill ratio.
    player._ratio = (points / total);

    // Creates a copy of the player.
    player._player._name = Create(target._name._data);
    player._player._count = target._count;
}

void Destroy(RankedPlayer &player) {
    Destroy(player._player);
    player._ratio = 0;
}

bool IsHigher(const RankedPlayer &one, const RankedPlayer &two) {
    if(one._ratio > two._ratio) {
        return true;
    }
    else if(one._ratio == two._ratio) {
        return (one._player._count > two._player._count);
    }
    return false;
}

void Initialize(Scoreboard &scoreboard) {
    scoreboard._players = nullptr;
    scoreboard._count = 0;
}

void Destroy(Scoreboard &scoreboard) {
    if(scoreboard._players != nullptr) {
        for(ElementSize i = 0; i < scoreboard._count; i++) {
            Destroy(scoreboard._players[i]);
        }
        free(scoreboard._players);
        scoreboard._players = nullptr;
    }
    scoreboard._count = 0;
}

int64_t FindRankedPlayer(const Scoreboard &scoreboard, const Player &player) {
    for(ElementSize i = 0; i < scoreboard._count; i++) {    
        // Looks for a player in case-insensitive mode.
        if(!Compare(scoreboard._players[i]._player._name, player._name, false)) {
            return i;
        }
    }
    return NOT_FOUND;
}

void AddRankedPlayer(Scoreboard &scoreboard, const RankedPlayer &target) {
    // Looks for the ranked player with the same name as target.
    int64_t index = FindRankedPlayer(scoreboard, target._player);
    if(index != NOT_FOUND) {
        RankedPlayer &destination = scoreboard._players[index];
        destination._player._count = target._player._count;
        destination._ratio = target._ratio;
        return;
    }
    // Inserts the ranked player in the right position.
    ElementSize i = 0;
    while(i < scoreboard._count && IsHigher(target, scoreboard._players[i])) {
        i++;
    }
    InsertRankedPlayer(scoreboard, target, i);
}

// Inserts a ranked player at a certain index in the score board.
void InsertRankedPlayer(Scoreboard &scoreboard, const RankedPlayer &target, ElementSize index) {
    RankedPlayer *temp = static_cast<RankedPlayer*>(realloc(scoreboard._players, (scoreboard._count + 1) * sizeof(RankedPlayer)));
    if(temp == NULL) {
        return;
    }
    scoreboard._players = temp;
    for(ElementSize i = scoreboard._count; i > index; i--) {
        scoreboard._players[i] = scoreboard._players[i - 1];
    }
    scoreboard._players[index] = target;
    scoreboard._count++;
}

void RemoveRankedPlayer(Scoreboard &scoreboard, ElementSize position) {
    if(position < scoreboard._count) {
        Destroy(scoreboard._players[position]);
        for(ElementSize i = position; i < scoreboard._count - 1; i++) {
            scoreboard._players[i] = scoreboard._players[i + 1];
        }
        scoreboard._count--;
    }
}

bool IsEmpty(const Scoreboard &scoreboard) {
    return scoreboard._players == nullptr || scoreboard._count == 0;
}

void Assign(RankedPlayer &target, const RankedPlayer &source) {
    // Destroy everything available in the target.
    Destroy(target);

    // Copy new values to the target.
    Assign(target._player._name, source._player._name);
    target._player._count = source._player._count;
    target._ratio = source._ratio;
}

void PrintScoreboard(const Scoreboard &scoreboard) {
    using namespace std;
    // Clears the screen.
    ClearConsole();

    // Checks if the scoreboard is empty.
    if(IsEmpty(scoreboard)) {
        PrintWith("The scoreboard is empty.", BrightRed);
        cout << "Press any key to continue..." << endl;
        InputKey();
        return;
    }

    // Finds the longest name in scoreboard.
    TextSize longest = scoreboard._players[0]._player._name._size;
    for(ElementSize i = 1; i < scoreboard._count; i++) {
        if(scoreboard._players[i]._player._name._size > longest) {
            longest = scoreboard._players[i]._player._name._size;
        }
    }

    // Prints the header of the grid.
    const Color headerColor = Yellow;

    // Prints the name as the header.
    const char *nameHeader = "Name";
    PrintWith(nameHeader, headerColor);

    // Fills the blanks.
    for(TextSize i = 0; i < longest - strlen(nameHeader); i++) {
        cout << " ";
    }
    cout << '\t';

    // Prints the count as the header.
    const char *pointHeader = "Point";
    PrintWith(pointHeader, headerColor);
    cout << '\t';

    // Prints the fill ratio as the header.
    const char *ratioHeader = "Ratio";
    PrintWith(ratioHeader, headerColor);
    cout << endl;

    // Draws a seperator
    const int length = longest + strlen(nameHeader) + strlen(pointHeader) + strlen(ratioHeader);
    for(int i = 0; i < length; ++i) {
        cout << '=';
    }
    cout << endl;

    // Draws the ranked players.
    for(int i = 0; i < scoreboard._count; ++i) {
        const RankedPlayer &player = scoreboard._players[i];

        // Prints the name of the player.
        PrintWith(player._player._name, Cyan);

        // Fills with blank.
        for(TextSize j = 0; j < longest - player._player._name._size; j++) {
            cout << " ";
        }
        cout << '\t';

        // Prints the total points.
        cout << player._player._count << '\t';

        // Prints the ratio.
        cout << player._ratio << endl;
    }

    // Draws a seperator
    for(int i = 0; i < length; ++i) {
        cout << '=';
    }

    cout << endl;
}