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

// Prints a piece of text in a specific color.
void Print(const Text &text, const Color &color);

// Prints a piece of text in a specific color.
void Print(const char *string, const Color &color);

// Resets the foreground color of the console.
void ResetForeground();

#endif