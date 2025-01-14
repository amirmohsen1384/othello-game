#ifndef TABLE_H
#define TABLE_H

#include "point.h"
#include <cstdint>
#include <iostream>

/* Othello table is a 2D array containing integers.
 * Let me call each integer belonging to the table a cell. */
typedef int Cell;
typedef int64_t Dimension;

// Describes an othello table.
typedef struct Table {
    Cell*       _data;
    Dimension   _width;
    Dimension   _height;
}
Table;

// Checks whether the point is in the othello table.
bool IsValid(const Table &, const Point &);

// Creates an othello table.
Table Create(int, int); 

// Checks whether an othello cell is empty.
bool IsEmpty(const Cell *pointer);

// Returns a reference at a certain point of the table.
Cell* PointAt(const Table &, const Point &);

// Checks whether an othello table is full.
bool IsFull(const Table &);

// Destroys the table.
void Destroy(Table &);

// Initializes a table.
void Initialize(Table &);

// Checks if a cell belongs to a player.
bool BelongsToPlayer(const Table &, const Point &);

// Serializes a table into the stream.
std::ofstream& operator<<(std::ofstream &stream, const Table &table);
std::ifstream& operator>>(std::ifstream &stream, Table &table);


#endif