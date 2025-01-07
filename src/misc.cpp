#include "../include/misc.h"
#include <windows.h>
#include <cstdlib>

void ResetScreen() {
    using namespace std;
    std::system("cls");
}

void GoToLocation(const Point &point) {
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;
    position.X = point._x;
    position.Y = point._y;
    SetConsoleCursorPosition(output, position);
}

void Pause(int duration) {
    Sleep(duration * 1000);
}