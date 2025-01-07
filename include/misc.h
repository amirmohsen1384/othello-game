#ifndef MISC_H
#define MISC_H

#include "point.h"

// Clears the screen and resets the pointer to the beginning.
void ResetScreen();

// Moves the cursor to a certain location.
void GoToLocation(const Point &point);

// Makes a pause for the application.
void Pause(int duration);

#endif