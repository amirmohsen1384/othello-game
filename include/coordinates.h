#ifndef COORDINATES_H
#define COORDINATES_H

#include "point.h"

typedef struct Coordinates {
    Point   *_data;
    int     _size;
}
Coordinates;

// Inserts a point to the container at a given index.
bool Insert(Coordinates &, const Point &, int);

// Appends a point to the container.
bool Append(Coordinates &, const Point &);

// Removes a point located at index from the container.
bool Remove(Coordinates &, int);

// Prepends a point to the container.
bool Prepend(Coordinates &, const Point &);

// Destroys a container.
void Destroy(Coordinates &);

#endif