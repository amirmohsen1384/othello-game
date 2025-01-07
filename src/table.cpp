#include "../include/table.h"
#include <cstdlib>

bool IsEmpty(const Table &table, const Point &cell) {
    Cell* pointer = PointAt(table, cell);
    if(pointer != nullptr) {
        return *pointer == -1;

    } else {
        return true;

    }
}

Cell* PointAt(const Table &table, const Point &cell) {
    if(!IsValid(table, cell)) {
        return nullptr;
    }
    const int width = table._width;
    const int position = cell._x * width + cell._y;
    return (table._data + position);
}

bool IsFull(const Table &table) {
    for(int i = 0; i < table._width; ++i) {
        for(int j = 0; j < table._height; ++j) {
            Point point = {i, j};
            if(IsEmpty(table, point)) {
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
    for(int i = 0; i < table._width; ++i) {
        for(int j = 0; j < table._height; ++j) {
            Cell *cell = PointAt(table, {i, j});
            *cell = -1;
        }
    }
}