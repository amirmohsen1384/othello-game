#include "../include/system.h"
#include <windows.h>
#include <cstdlib>

void ClearConsole() {
    using namespace std;
    std::system("cls");
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