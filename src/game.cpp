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

Player* CreatePlayer(const Text &text) {
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

void ToggleTurn(TurnInfo &turn) {
    turn = !turn;
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

void PutPiece(Table &table, const Point &point, TurnInfo &turn) {
    // Put a piece in the the specified position
    *PointAt(table, point) = turn;

    // Update surrounded pieces
    UpdateSurroundedPieces(table, point);

    // Give the opponent the turn
    ToggleTurn(turn);
}

MatchInfo* Define(int width, int height, const TurnInfo &initial) {
    MatchInfo* game = new MatchInfo;

    game->_environment = Create(width, height);
    game->_status = Undefined;
    game->_turn = initial;

    Player *user = &game->_players[PLAYER_USER];
    Player *opponent = &game->_players[PLAYER_OPPONENT];
    
    user->_name._data = opponent->_name._data = nullptr;
    user->_name._size = opponent->_name._size = 0;
    user->_count = opponent->_count = 2;
    
    return game;
}

MatchInfo* Define(int width, int height, const Text &playerName, const Text &opponentName, const TurnInfo &initial)
{
    MatchInfo *game = Define(width, height, initial);
    if(game == nullptr) {
        return nullptr;
    }
    
    Player *user = &game->_players[PLAYER_USER];
    Player *opponent = &game->_players[PLAYER_OPPONENT];

    user->_name = playerName;
    opponent->_name = opponentName;
    
    return game;
}

void Delete(MatchInfo *game)
{
    if(game == nullptr) {
        Destroy(game->_environment);
        delete game;
        game = nullptr;
    }
}

bool MatchContinues(MatchInfo &game) {
    Coordinates one = GetLegalPoints(game._environment, game._turn);
    if(IsEmpty(one)) {
        ToggleTurn(game._turn);
        Coordinates two = GetLegalPoints(game._environment, game._turn);
        if(IsEmpty(two)) {
            Destroy(one);
            Destroy(two);
            return false;
        
        } else {
            Destroy(one);
            Destroy(two);
            return true;
        }
    }
    Destroy(one);
    return true;
}

#include <iostream>
#include "../include/system.h"

void Execute(MatchInfo &game) {
    using namespace std;

    // Creates some references to the players.
    Player &user = game._players[PLAYER_USER];
    Player &opponent = game._players[PLAYER_OPPONENT];

    // Clears the whole screen.
    ClearConsole();

    // Get the name of players.
    

    if(IsEmpty(user._name) || IsEmpty(opponent._name)) {
        PrintWith("Enter the name of player 1: ", BrightCyan);
        Text userName = GetLine();
        ClearConsole();

        PrintWith("Enter the name of player 2: ", BrightGreen);
        Text opponentName = GetLine();
        ClearConsole();

        user._name = userName;
        opponent._name = opponentName;
    }

    do {
        // Creates a reference to the current player
        Player &current = (game._turn == PLAYER_USER) ? user : opponent;
        
        // Prints the whole match
        PrintMatch(game);

        // Asks to select a position
        if(game._status == IllegalPoint) {
            PrintWith("You have entered an invalid point.\n", Red);
        }
        PrintWith(current._name, (game._turn == PLAYER_USER) ? PLAYER_COLOR : OPPONENT_COLOR);
        cout << ':' << '\n' << ' ' << "Please select a place in the table: ";

        Point temp;
        GetPoint(temp);

        // Checks if the entered point is legal
        if(!IsLegal(game._environment, game._turn, temp)) {
            game._status = IllegalPoint;

        } else {
            PutPiece(game._environment, temp, game._turn);
            UpdatePlayersCount(game._environment, game._players);
            game._status = Undefined;

        }
        ClearConsole();
    }
    while(MatchContinues(game));

    if(user._count > opponent._count) {
        game._status = UserWon;
    }

    else if(user._count == opponent._count) {
        game._status = GameDraw;
    }

    else {
        game._status = OpponentWon;

    }
}



