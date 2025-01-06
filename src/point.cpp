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
    Forward(point, 1);
}

Point Backward(const Point &point) {
    Backward(point, 1);
}

Point TurnLeft(const Point &point) {
    TurnLeft(point, 1);
}

Point TurnRight(const Point &point) {
    TurnRight(point, 1);
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