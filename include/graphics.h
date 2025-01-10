#ifndef GRAHICS_H
#define GRAHICS_H

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

// Sets the foreground color of the console.
void SetForeground(const Color &color);

// Sets the background color of the console.
void SetBackground(const Color &color);

// Sets the appearance of the console.
void SetAppearance(const Color &foreground, const Color &background);

// Prints a piece of text in a specific color.
void Print(const Text &text, const Color &color);

// Prints a piece of text in a specific color.
void Print(const char *string, const Color &color);

// Resets the foreground color of the console.
void ResetForeground();

// Resets the background color of the console.
void ResetBackground();

// Resets the appearance of the console.
void ResetAppearance();

#endif