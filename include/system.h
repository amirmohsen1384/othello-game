#ifndef MISC_H
#define MISC_H

#include "point.h"

// Clears the screen and resets the pointer to the beginning.
void ClearConsole();

// Makes a pause for the application.
void Pause(int duration);

// Waits for the user to press a key.
int InputKey();

#endif