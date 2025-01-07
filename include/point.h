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
Point Forward(const Point &point, int step);

// Moves down a point by step.
Point Backward(const Point &point, int step);

// Moves left a point by step.
Point TurnLeft(const Point &point, int step);

// Moves right a point by step.
Point TurnRight(const Point &point, int step);

// Moves up a point by one.
Point Forward(const Point &point);

// Moves down a point by one.
Point Backward(const Point &point);

// Moves left a point by one.
Point TurnLeft(const Point &point);

// Moves right a point by one.
Point TurnRight(const Point &point);

// Gets a point from the input stream.
void GetPoint(Point &point);

// Prints a points to the output stream.
void PrintPoint(const Point &point);

#endif