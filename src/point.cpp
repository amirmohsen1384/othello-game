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

Point MoveTop(const Point &point, int step) {
    return Subtract(point, {0, step});
}

Point MoveBottom(const Point &point, int step) {
    return Add(point, {0, step});
}

Point MoveLeft(const Point &point, int step) {
    return Subtract(point, {step, 0});
}

Point MoveRight(const Point &point, int step) {
    return Add(point, {step, 0});
}

Point MoveTop(const Point &point) {
    return MoveTop(point, 1);
}

Point MoveBottom(const Point &point) {
    return MoveBottom(point, 1);
}

Point MoveLeft(const Point &point) {
    return MoveLeft(point, 1);
}

Point MoveRight(const Point &point) {
    return MoveRight(point, 1);
}

Point MoveTopLeft(const Point &point, int step) {
    Point temp = MoveTop(point);
    return MoveLeft(temp);
}

Point MoveTopRight(const Point &point, int step) {
    Point temp = MoveTop(point);
    return MoveRight(temp);
}

Point MoveBottomLeft(const Point &point, int step) {
    Point temp = MoveBottom(point);
    return MoveLeft(temp);
}

Point MoveBottomRight(const Point &point, int step) {
    Point temp = MoveBottom(point);
    return MoveRight(temp);
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

bool IsIdentical(const Point &one, const Point &two) {
    return one._x == two._x && one._y == two._y;
}