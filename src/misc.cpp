#include "../include/misc.h"
#include <windows.h>
#include <cstdlib>

void ClearConsole() {
    using namespace std;
    std::system("cls");
}

void GoToLocation(const Point &point) {
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    if (output == INVALID_HANDLE_VALUE) {
        return;
    }
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    if (!GetConsoleScreenBufferInfo(output, &bufferInfo)) {
        return;
    }
    COORD position;
    position.X = point._x;
    position.Y = point._y;
    if (position.X < 0 || position.X >= bufferInfo.dwSize.X || position.Y < 0 || position.Y >= bufferInfo.dwSize.Y) {
        COORD newSize = bufferInfo.dwSize;
        if(bufferInfo.dwSize.Y > position.Y + 1) {
            newSize.Y = bufferInfo.dwSize.Y;
        } else {
            newSize.Y = position.Y + 1;
        }
        if(bufferInfo.dwSize.X > position.X + 1) {
            newSize.X = bufferInfo.dwSize.X;
        } else {
            newSize.X = position.X + 1;
        }
        if (!SetConsoleScreenBufferSize(output, newSize)) {
            return;
        }
    }
    SetConsoleCursorPosition(output, position);
}

int InputKey() {
    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
    DWORD dwMode, cNumRead;
    INPUT_RECORD irInBuf;
    if (input == INVALID_HANDLE_VALUE) {
        return -1;
    }
    else if (!GetConsoleMode(input, &dwMode)) {
        return -1;
    }
    dwMode &= ~ENABLE_ECHO_INPUT;
    dwMode &= ~ENABLE_LINE_INPUT;
    if (!SetConsoleMode(input, dwMode)) {
        return -1;
    }
    while (true) {
        if (!ReadConsoleInput(input, &irInBuf, 1, &cNumRead)) {
            return -1;
        }
        if (irInBuf.EventType == KEY_EVENT && irInBuf.Event.KeyEvent.bKeyDown) {
            return irInBuf.Event.KeyEvent.wVirtualKeyCode;
        }
    }
}

void Pause(int duration) {
    Sleep(duration * 1000);
}