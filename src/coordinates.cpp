#include "../include/coordinates.h"
#include <cstdlib>

int Bound(int min, int value, int max) {
    if(value < min) {
        value = min;
    } 
    else if (value > max) {
        value = max;
    }
    return value;
}

void Destroy(Coordinates &container) {
    free(container._data);
    container._size = 0;
    container._data = nullptr;
}

bool Insert(Coordinates &container, const Point &point, int index) {
    container._data = (Point*) realloc(container._data, ++container._size * sizeof(Point));
    if(container._data == NULL) {
        return false;
    }
    Point *data = container._data;
    int position = Bound(0, index, container._size);
    for(int i = container._size - 2; i >= position; i--) {
        *(data + i + 1) = *(data + i);
    }
    *(data + position) = point;
    return true;
}

bool Remove(Coordinates &container, int index) {
    Point *data = container._data;
    int position = Bound(0, index, container._size);
    for(int i = position; i < container._size - 1; ++i) {
        *(data + i) = *(data + i + 1);
    }
    container._data = (Point*) realloc(container._data, --container._size * sizeof(Point));
    return container._data != NULL;
}

bool Append(Coordinates &container, const Point &point) {
    return Insert(container, point, container._size);
}

bool Prepend(Coordinates &container, const Point &point) {
    return Insert(container, point, 0);
}

bool IsEmpty(const Coordinates &container) {
    return container._data == NULL || container._size == 0;
}