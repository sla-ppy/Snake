#include <iostream>

#include "game.h"

struct Node {
public:
	int pos_x { 0 };
	int pos_y { 0 };
};

int main() {
	Game* game = new Game;

	game->init();
	game->update();
	game->deinit();

	delete game;
	
	return 0;
}