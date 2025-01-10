#include "../include/graphics.h"
#include <windows.h>

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

void Print(const Text &text, const Color &color) {
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

void Print(const char *string, const Color &color) {
    Text text = Create(string);
    Print(text, color);
    Destroy(text);
}

void ResetForeground() {
    SetForeground(White);
}