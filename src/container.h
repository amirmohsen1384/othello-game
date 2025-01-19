#ifndef CONTAINER_H
#define CONTAINER_H

#include "point.h"

#define NOT_FOUND -1

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

// Finds a specific point in the coordinate
int Find(const Coordinates &, const Point &);

#include "text.h"

/* A high-level interface to work with a range of choices. */
typedef struct Choice {
    Text*       _choices;
    size_t      _count;
}
ChoiceList;

// Initializes a choice list.
void Initialize(ChoiceList &list);

// Appends a choice to the list.
bool Append(ChoiceList &list, const Text &description);

// Destroys a choice list.
void Destroy(ChoiceList &list);

// Removes a choice from the list.
bool Remove(ChoiceList &list, int index);

// Checks whether the list is empty.
bool IsEmpty(const ChoiceList &list);

// Shows up a menu of choices.
int Execute(const ChoiceList &list, const Text &description);
int Execute(const ChoiceList &list, const char *description);

// Finds a specific choice in the list.
int Find(const ChoiceList &list, const Text &description);

#endif