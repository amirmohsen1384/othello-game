#ifndef COORDINATES_H
#define COORDINATES_H

#include "point.h"

/* A basic type to work with a dynamic array of points. */
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

// Checks whether the container is empty.
bool IsEmpty(const Coordinates &);

#define NOT_FOUND -1

// Finds a specific point in the coordinate
int Find(const Coordinates &, const Point &);

#endif