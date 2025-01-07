#ifndef TABLE_H
#define TABLE_H

#include "coordinates.h"
#include "point.h"

/* Othello table is a 2D array containing integers.
 * Let me call each integer belonging to the table a cell. */
typedef int Cell;

// Describes an othello table.
typedef struct Table {
    Cell* _data;
    int _height;
    int _width;
}
Table;

// Checks whether the point is in the othello table.
bool IsValid(const Table &, const Point &);

// Creates an othello table.
Table Create(int, int); 

// Checks whether an othello cell is empty.
bool IsEmpty(const Table &, const Point &);

// Returns a reference at a certain point of the table.
Cell* PointAt(const Table &, const Point &);

// Checks whether an othello table is full.
bool IsFull(const Table &);

// Destroys the table.
void Destroy(Table &);

// Initializes a table.
void Initialize(Table &);

// Checks whether a point is legal for a player.
bool IsLegal(const Table &, int, const Point &);

// Returns a list of legal points for a player.
Coordinates GetLegalPoints(Table &, int);

#endif