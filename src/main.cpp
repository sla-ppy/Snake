#include <iostream>
#include <sstream>

#include "game.h"

int main() {
	Game* game = new Game;

	game->init();
	game->update();
	game->deinit();

	delete game;
	
	return 0;
}