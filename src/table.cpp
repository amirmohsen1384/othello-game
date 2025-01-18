#include <iostream>
#include <cstdlib>
#include "system.h"
#include "table.h"
#include "game.h"

#define EMPTY_CELL -1

bool IsEmpty(const Cell *pointer) {
    if(pointer == nullptr) {
        return true;
    }
    return *pointer == EMPTY_CELL;
}

Cell* PointAt(const Table &table, const Point &cell) {
    if(!IsValid(table, cell)) {
        return nullptr;
    }
    const int width = table._width;
    const int position = cell._y * width + cell._x;
    return (table._data + position);
}

bool IsFull(const Table &table) {
    for(int j = 0; j < table._height; ++j) {
        for(int i = 0; i < table._width; ++i) {
            Cell *pointer = PointAt(table, {i, j});
            if(IsEmpty(pointer)) {
                return false; 
            }
        }
    }
    return true;
}

Table Create(int width, int height) {
    Table table = {NULL, 0, 0};
    table._data = (Cell*) calloc(width * height, sizeof(Cell));
    if(table._data == nullptr) {
        return table;
    }
    table._width = width;
    table._height = height;
    Initialize(table);
    return table;
}

bool IsValid(const Table &table, const Point &point) {
    const int width = table._width;
    const int height = table._height;
    return (point._x >= 0 && point._x < width) && (point._y >= 0 && point._y < height);
}

void Destroy(Table &table) {
    free(table._data);
    table._width = 0;
    table._height = 0;
    table._data = nullptr;
}

void Initialize(Table &table) {
    for(int j = 0; j < table._height; ++j) {
        for(int i = 0; i < table._width; ++i) {
            Cell *cell = PointAt(table, {i, j});
            *cell = EMPTY_CELL;
        }
    }

    Point point = {0, 0};
    point._x = static_cast<int>((table._width - 1) / 2);
    point._y = static_cast<int>((table._height - 1) / 2);

    Cell *one = PointAt(table, point);
    *one = PLAYER_USER;
    point = MoveRight(point);

    Cell *two = PointAt(table, point);
    *two = PLAYER_OPPONENT;
    point = MoveBottom(point);

    Cell *three = PointAt(table, point);
    *three = PLAYER_USER;
    point = MoveLeft(point);
    
    Cell *four = PointAt(table, point);
    *four = PLAYER_OPPONENT;
}

bool BelongsToPlayer(const Table &table, const Point &point) {
    Cell *place = PointAt(table, point);
    return !IsEmpty(place) && IsValid(table, point);
}