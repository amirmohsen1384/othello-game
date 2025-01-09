#include "../include/graphics.h"
#include <windows.h>

int ToForeground(const Color &color) {
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
            return -1;
        }
    }
}
int ToBackground(const Color &color) {
    switch(color) {
        case Black: {
            return 0;
        }
        case Gray: {
            return BACKGROUND_INTENSITY;
        }
        case Blue: {
            return BACKGROUND_BLUE;
        }
        case BrightBlue: {
            return BACKGROUND_BLUE | BACKGROUND_INTENSITY;
        }
        case Green: {
            return BACKGROUND_GREEN;
        }
        case BrightGreen: {
            return BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        }
        case Red: {
            return BACKGROUND_RED;
        }
        case BrightRed: {
            return BACKGROUND_RED | BACKGROUND_INTENSITY;
        }
        case Cyan: {
            return BACKGROUND_BLUE | BACKGROUND_GREEN;
        }
        case BrightCyan: {
            return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        }
        case Magenta: {
            return BACKGROUND_BLUE | BACKGROUND_RED;
        }
        case BrightMagenta: {
            return BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
        }
        case Yellow: {
            return BACKGROUND_GREEN | BACKGROUND_RED;
        }
        case BrightYellow: {
            return BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
        }
        case White: {
            return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
        }
        default: {
            return -1;
        }
    }
}

void SetForeground(const Color &color) {
    // Converts the color into an integer
    int value = ToForeground(color);

    // Set the foreground color
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, value);
}

void SetBackground(const Color &color) {
    // Converts the color into an integer
    int value = ToBackground(color);

    // Set the foreground color
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, value);
}

void SetAppearance(const Color &foreground, const Color &background) {
    SetForeground(foreground);
    SetBackground(background);
}

void Print(const Text &text, const Color &color) {
    // Create a reference to the output
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get the attributes of the output
    CONSOLE_SCREEN_BUFFER_INFO information;
    GetConsoleScreenBufferInfo(output, &information);
    WORD initial = information.wAttributes;

    // Print the text
    SetForeground(color);
    Print(text);

    // Reset the attributes of the output
    SetConsoleTextAttribute(output, initial);
}

void Print(const char *string, const Color &color) {
    Text text = Create(string);
    Print(text, color);
}

void ResetForeground() {
    SetForeground(White);
}

void ResetBackground() {
    SetBackground(Black);
}

void ResetAppearance() {
    ResetForeground();
    ResetBackground();
}