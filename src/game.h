#ifndef GAME_H
#define GAME_H

#include <functional>
#include <string>

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
    Map map;    
    Apple apple;

    void update();
    void inputCheck(Direction& dir);

    Game();
    Game(const Game&) = delete;
};

#endif // GAME_H