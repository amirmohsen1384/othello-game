#include <windows.h>
#include <shlobj.h>
#include "system.h"
#include <cstdlib>

void ClearConsole() {
    system("cls");
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

WORD ToForeground(const Color &color) {
    switch(color) {
        case Black: {
            return 0;
        }
        case Gray: {
            return FOREGROUND_INTENSITY;
        }
        case Blue: {
            return FOREGROUND_BLUE;
        }
        case BrightBlue: {
            return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        }
        case Green: {
            return FOREGROUND_GREEN;
        }
        case BrightGreen: {
            return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        }
        case Red: {
            return FOREGROUND_RED;
        }
        case BrightRed: {
            return FOREGROUND_RED | FOREGROUND_INTENSITY;
        }
        case Cyan: {
            return FOREGROUND_BLUE | FOREGROUND_GREEN;
        }
        case BrightCyan: {
            return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        }
        case Magenta: {
            return FOREGROUND_BLUE | FOREGROUND_RED;
        }
        case BrightMagenta: {
            return FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
        }
        case Yellow: {
            return FOREGROUND_GREEN | FOREGROUND_RED;
        }
        case BrightYellow: {
            return FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
        }
        case White: {
            return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
        }
        default: {
            return 0;
        }
    }
}

WORD GetInitialInfo(HANDLE output) {
    CONSOLE_SCREEN_BUFFER_INFO information;
    GetConsoleScreenBufferInfo(output, &information);
    return information.wAttributes;
}

void SetForeground(const Color &color) {
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

    // Converts the color into an integer
    WORD value = ToForeground(color);

    // Sets the foreground color
    SetConsoleTextAttribute(output, value);
}

void PrintWith(const Text &text, const Color &color) {
    // Create a reference to the output
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get the attributes of the output
    WORD initial = GetInitialInfo(output);

    // Print the text
    SetForeground(color);
    Print(text);

    // Reset the attributes of the output
    SetConsoleTextAttribute(output, initial);
}

void PrintWith(const char *string, const Color &color) {
    Text text = Create(string);
    PrintWith(text, color);
    Destroy(text);
}

void ResetForeground() {
    SetForeground(White);
}

Text GetTempFolder() {
    DWORD result = 0;
    Text target = {NULL, 0};
    char temporary[MAX_PATH];
    result = GetTempPathA(MAX_PATH, temporary);
    if(result > 0 && result < MAX_PATH) {
        Initialize(target, temporary);
    }
    return target;
}

void MakeBeep() {
    DWORD frequency = 750;
    DWORD duration = 600;
    Beep(frequency, duration);
}

bool RemoveFile(const Text &path) {
    if(IsEmpty(path)) {
        return false;
    }
    return remove(path._data);
}

Text GetLocalFolder() {
    PWSTR path = nullptr;
    Text target = {NULL, 0};
    HRESULT result = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path);
    if(SUCCEEDED(result)) {
        Initialize(target, reinterpret_cast<char*>(path));
        CoTaskMemFree(path);
    }
    return target;
}