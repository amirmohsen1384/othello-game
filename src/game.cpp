#include "../include/game.h"
#include "../include/misc.h"

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

bool IsLegal(const Table &table, PlayerNumber player, const Point &point, Direction direction) {
    Point temp = {-1, -1}, pos = point;
    const int opponent = ~player;
    Cell *pointer = nullptr;
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
        if(!IsValid(table, temp)) {
            break;
        }
        pointer = PointAt(table, pos);
        if(IsEmpty(pointer)) {
            break;
        }
        pos = temp;
        if(*pointer == opponent) {
            ++count;
        }
    }
    while(*pointer != player);

    if(pointer != nullptr) {
        if(*pointer == player && count > 0) {
            return true;
        }
    }

    return false;
}

bool IsLegal(const Table &table, PlayerNumber player, const Point &point) {
    if(!IsEmpty(PointAt(table, point))) {
        return false;
    }
    else if(IsLegal(table, player, point, Top)) {
        return true;
    }
    else if(IsLegal(table, player, point, Bottom)) {
        return true;
    }
    else if(IsLegal(table, player, point, Left)) {
        return true;
    }
    else if(IsLegal(table, player, point, Right)) {
        return true;
    }
    else if(IsLegal(table, player, point, TopLeft)) {
        return true;
    }
    else if(IsLegal(table, player, point, TopRight)) {
        return true;
    }
    else if(IsLegal(table, player, point, BottomLeft)) {
        return true;
    }
    else if(IsLegal(table, player, point, BottomRight)) {
        return true;
    }
    else {
        return false;
    }
}

Coordinates GetLegalPoints(const Table &table, PlayerNumber player) {
    Coordinates result = {nullptr, 0};
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

void UpdatePlayersCount(const Table &table, Player *players) {
    if(players == nullptr) {
        return;
    }
    for(int i = 0; i < table._width; ++i) {
        for(int j = 0; j < table._height; ++j) {
            Cell *pointer = PointAt(table, {i, j});
            if(!IsEmpty(pointer)) {
                players[*pointer]._count++;
            }
        }
    }
}