#ifndef GAME_H
#define GAME_H

#include <string>
#include <functional>

class Game {
public:
	Game() {}
	~Game() {}

	void init();
	void update();
	void deinit();
};

#endif // GAME_H