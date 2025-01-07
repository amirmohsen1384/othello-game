#include "../include/point.h"

Point Add(const Point &one, const Point &two) {
    Point result = {0, 0};
    result._x = one._x + two._x;
    result._y = one._y + two._y;
    return result;
}

Point Subtract(const Point &one, const Point &two) {
    Point result = {0, 0};
    result._x = one._x - two._x;
    result._y = one._y - two._y;
    return result;
}

Point Transposed(const Point &point) {
    Point result = {0, 0};
    result._x = point._y;
    result._y = point._x;
    return result;
}

Point Forward(const Point &point, int step) {
    return Subtract(point, {0, step});
}

Point Backward(const Point &point, int step) {
    return Add(point, {0, step});
}

Point TurnLeft(const Point &point, int step) {
    return Subtract(point, {step, 0});
}

Point TurnRight(const Point &point, int step) {
    return Add(point, {step, 0});
}

Point Forward(const Point &point) {
    return Forward(point, 1);
}

Point Backward(const Point &point) {
    return Backward(point, 1);
}

Point TurnLeft(const Point &point) {
    return TurnLeft(point, 1);
}

Point TurnRight(const Point &point) {
    return TurnRight(point, 1);
}

Point MoveTopLeft(const Point &point, int step) {
    return Subtract(point, {step, step});
}

Point MoveTopRight(const Point &point, int step) {
    return Add(point, {step, -step});
}

Point MoveBottomLeft(const Point &point, int step) {
    return Add(point, {-step, step});
}

Point MoveBottomRight(const Point &point, int step) {
    return Add(point, {step, step});
}

Point MoveTopLeft(const Point &point) {
    return MoveTopLeft(point, 1);
}

Point MoveTopRight(const Point &point) {
    return MoveTopRight(point, 1);
}

Point MoveBottomLeft(const Point &point) {
    return MoveBottomLeft(point, 1);
}

Point MoveBottomRight(const Point &point) {
    return MoveBottomRight(point, 1);
}

#include <iostream>
void GetPoint(Point &point) {
    using namespace std;
    cin >> point._x >> point._y;
}

void PrintPoint(const Point &point) {
    using namespace std;
    cout << '(' << point._x << ", " << point._y << ')' << std::endl;
}