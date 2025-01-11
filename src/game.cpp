#include "../include/game.h"

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

Player* Create(const Text &text) {
    Player *player = new Player;
    player->_name = text;
    player->_count = 0;
    return player;
}

void Destroy(Player &player) {
    Destroy(player._name);
    player._count = 0;
}

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
        pointer = PointAt(table, temp);
        if(pointer == nullptr) {
            break;

        } else if(IsEmpty(pointer)) {
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

bool IsLegal(const Table &table, Piece player, const Point &point) {
    if(!IsEmpty(PointAt(table, point))) {
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
    if(players == nullptr) {
        return;
    }
    for(int j = 0; j < table._height; ++j) {
        for(int i = 0; i < table._width; ++i) {
            Cell *pointer = PointAt(table, {i, j});
            if(!IsEmpty(pointer)) {
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

void PutPiece(Table &table, const Point &point, TurnInfo &turn, Player *players) {
    // Put a piece in the the specified position
    *PointAt(table, point) = turn;

    // Update surrounded pieces
    UpdateSurroundedPieces(table, point);

    // Update the count of pieces for each player
    UpdatePlayersCount(table, players);

    // Give the opponent the turn
    turn = !turn;
}