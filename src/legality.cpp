#include "../include/table.h"
#include <cstdlib>

typedef enum Direction {
    Top = 0,
    Bottom,
    Left,
    Right,
    TopLeft,
    BottomRight,
    TopRight,
    BottomLeft
} 
Direction;

bool IsLegalInDirection(const Table &table, int player, const Point &point, Direction direction) {
    const int opponent = ~player;
    Point temp = {-1, -1};
    Cell *cell = nullptr;
    Point pos = point;
    int count = 0;
    do {
        switch(direction) {
            case Top: {
                temp = MoveTop(pos);
                break;
            }
            case Bottom: {
                temp = MoveBottom(pos);
                break;
            }
            case Left: {
                temp = MoveLeft(pos);
                break;
            }
            case Right: {
                temp = MoveRight(pos);
                break;
            }
            case TopLeft: {
                temp = MoveTopLeft(pos);
                break;
            }
            case TopRight: {
                temp = MoveTopRight(pos);
                break;
            }
            case BottomLeft: {
                temp = MoveBottomLeft(pos);
                break;
            }
            case BottomRight: {
                temp = MoveBottomRight(pos);
                break;
            }
        }
        if(!IsValid(table, temp) || IsEmpty(table, temp)) {
            break;
        }
        pos = temp;
        if(*(cell = PointAt(table, pos)) == opponent) {
            ++count;
        }
    }
    while(*cell != player);
    if(cell != nullptr) {
        if(*cell == player && count > 0) {
            return true;
        }
    }
    return false;
}

bool IsLegal(const Table &table, int player, const Point &point) {
    if(!IsEmpty(table, point)) {
        return false;
    }
    else if(IsLegalInDirection(table, player, point, Top)) {
        return true;
    }
    else if(IsLegalInDirection(table, player, point, Bottom)) {
        return true;
    }
    else if(IsLegalInDirection(table, player, point, Left)) {
        return true;
    }
    else if(IsLegalInDirection(table, player, point, Right)) {
        return true;
    }
    else if(IsLegalInDirection(table, player, point, TopLeft)) {
        return true;
    }
    else if(IsLegalInDirection(table, player, point, TopRight)) {
        return true;
    }
    else if(IsLegalInDirection(table, player, point, BottomLeft)) {
        return true;
    }
    else if(IsLegalInDirection(table, player, point, BottomRight)) {
        return true;
    }
    else {
        return false;
    }
}

Coordinates GetLegalPoints(const Table &table, int player) {
    Coordinates result = {NULL, 0};
    for(int i = 0; i < table._width; ++i) {
        for(int j = 0; j < table._height; ++j) {
            Point point = {i, j};
            if(IsLegal(table, player, point)) {
                Append(result, {i, j});
            }
        }
    }
    return result;
}