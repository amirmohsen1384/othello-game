#include "game.h"

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

bool IsLegal(const Table &table, Piece player, const Point &point, Direction direction) {
    Cell *pointer = PointAt(table, point);
    Point temp = {-1, -1}, pos = point;
    const Piece opponent = !player;
    if(!IsEmpty(pointer)) {
        return false;
    }
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
        if(!BelongsToPlayer(table, temp)) {
            break;
        }
        pos = temp;
        pointer = PointAt(table, pos);
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

void ToggleTurn(TurnInfo &turn) {
    turn = !turn;
}

bool IsLegal(const Table &table, Piece player, const Point &point) {
    Cell *pointer = PointAt(table, point);
    if(!IsEmpty(pointer)) {
        return false;
    }
    for(int i = 0; i < 8; ++i) {
        if(IsLegal(table, player, point, static_cast<Direction>(i))) {
            return true;
        }
    }
    return false;
}

Coordinates GetLegalPoints(const Table &table, Piece player) {
    Coordinates result = {nullptr, 0};
    for(int j = 0; j < table._height; ++j) {
        for(int i = 0; i < table._width; ++i) {
            Point point = {i, j};
            if(IsLegal(table, player, point)) {
                Append(result, point);
            }
        }
    }
    return result;
}

void UpdatePlayersCount(const Table &table, Player *players) {
    int opponent = 0, player = 0;
    for(int j = 0; j < table._height; ++j) {
        for(int i = 0; i < table._width; ++i) {
            if(BelongsToPlayer(table, {i, j})) {
                Cell *pointer = PointAt(table, {i, j});
                if(*pointer == PLAYER_USER) {
                    player++;
                } else {
                    opponent++;
                }
            }
        }
    }
    players[PLAYER_USER]._count = player;
    players[PLAYER_OPPONENT]._count = opponent;
}

void UpdateSurroundedPieces(Table &table, const Point &point, Direction direction) {
    Coordinates container = {nullptr, 0};
    Point temp = {-1, -1}, pos = point;
    if(!BelongsToPlayer(table, point)) {
        return;
    }
    Cell *pointer = nullptr;
    Piece player = *PointAt(table, point), opponent = !player;
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
        pointer = PointAt(table, temp);
        if(pointer == nullptr) {
            break;

        } else if(IsEmpty(pointer)) {
            break;

        }
        pos = temp;
        if(*pointer == opponent) {
            Append(container, pos);
        }
    }
    while(*pointer != player);

    if(pointer != nullptr) {
        if(*pointer == player && container._size > 0) {
            for(int i = 0; i < container._size; ++i) {
                Cell *pointer = PointAt(table, container._data[i]);
                *pointer = !(*pointer);
            }
        }
    }

    Destroy(container);
}

void UpdateSurroundedPieces(Table &table, const Point &point) {
    if(!BelongsToPlayer(table, point)) {
        return;
    }
    for(int i = 0; i < 8; ++i) {
        UpdateSurroundedPieces(table, point, static_cast<Direction>(i));
    }
}

void PutPiece(Table &table, const Point &point, TurnInfo &turn) {
    Cell *position = PointAt(table, point);
    if(IsEmpty(position)) {
        *position = turn;
    }
    UpdateSurroundedPieces(table, point);
}
void Initialize(Player &player)
{
    player._name = {NULL, 0};
    player._count = 0;
}

void Initialize(Player &player, const char *name, Size count)
{
    player._name = Create(name);
    player._count = count;
}

void Destroy(Player &player) {
    Destroy(player._name);
    player._count = 0;
}