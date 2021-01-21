#ifndef GAME_H
#define GAME_H

#include <string>
#include <functional>
#include <vector>

#include "snake.h"
#include "map.h"

enum class Direction {
	NOTMOVING,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Game {
public:
	Snake* sHead{ nullptr };
	//std::vector<Snake> sCells;
	Map* map{ nullptr };
	Apple* apple{ nullptr };

	void update();
	void inputCheck(Direction& dir);
	void doMovement(Direction& dir);

	Game();
	Game(const Game&) = delete;
	~Game();
};

#endif // GAME_H