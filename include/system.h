#ifndef SYSTEM_H
#define SYSTEM_H

#include "point.h"
#include "text.h"

typedef enum {
    Black = 0,
    Gray,

    Blue,
    BrightBlue,

    Green,
    BrightGreen,

    Red,
    BrightRed,

    Cyan,
    BrightCyan,

    Magenta,
    BrightMagenta,

    Yellow,
    BrightYellow,

    White
}
Color;

// Clears the screen and resets the pointer to the beginning.
void ClearConsole();

// Makes a pause for the application.
void Pause(int duration);

// Waits for the user to press a key.
int InputKey();

// Sets the foreground color of the console.
void SetForeground(const Color &color);

// Prints a piece of text in a specific color.
void PrintWith(const Text &text, const Color &color);

// Prints a piece of text in a specific color.
void PrintWith(const char *string, const Color &color);

// Resets the foreground color of the console.
void ResetForeground();

#endif