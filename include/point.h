#ifndef POINT_H
#define POINT_H

/* This is a point containing two property
 * including the x and y positions. */
typedef struct Point {
    int _x;
    int _y;
}
Point;

// Adds two different points and returns the result.
Point Add(const Point &one, const Point &two);

// Subtracts two different points and returns the result. 
Point Subtract(const Point &one, const Point &two);

// Returns a transposed copy of the point.
Point Transposed(const Point &point);

// Moves up a point by step.
Point MoveTop(const Point &point, int step);

// Moves down a point by step.
Point MoveBottom(const Point &point, int step);

// Moves left a point by step.
Point MoveLeft(const Point &point, int step);

// Moves right a point by step.
Point MoveRight(const Point &point, int step);

// Moves up a point by one.
Point MoveTop(const Point &point);

// Moves down a point by one.
Point MoveBottom(const Point &point);

// Moves left a point by one.
Point MoveLeft(const Point &point);

// Moves right a point by one.
Point MoveRight(const Point &point);

// Gets a point from the input stream.
void GetPoint(Point &point);

// Prints a points to the output stream.
void PrintPoint(const Point &point);

// Moves a point to the top-left by step.
Point MoveTopLeft(const Point &point, int step);

// Moves a point to the top-right by step.
Point MoveTopRight(const Point &point, int step);

// Moves a point to the bottom-left by step.
Point MoveBottomLeft(const Point &point, int step);

// Moves a point to the bottm-right by step.
Point MoveBottomRight(const Point &point, int step);

// Moves a point to the top-left by one.
Point MoveTopLeft(const Point &point);

// Moves a point to the top-right by one.
Point MoveTopRight(const Point &point);

// Moves a point to the bottom-left by one.
Point MoveBottomLeft(const Point &point);

// Moves a point to the bottm-right by one.
Point MoveBottomRight(const Point &point);

#endif