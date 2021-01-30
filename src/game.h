#ifndef GAME_H
#define GAME_H

#include <functional>
#include <string>
//#include <vector>

#include "map.h"
#include "snake.h"

enum class Direction {
    NOTMOVING,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Game {
public:
    Snake* sHead { nullptr };
    //std::vector<Snake> sCells;
    Map* map { nullptr };
    Apple* apple { nullptr };
    //std::vector<Snake*> sCells{ nullptr };

    void update();
    void inputCheck(Direction& dir);
    void doMovement(Direction& dir);

    Game();
    Game(const Game&) = delete;
    ~Game();
};

#endif // GAME_H