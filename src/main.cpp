#include <iostream>
#include <thread>

#include "util.h"

struct Node {
public:
	int pos_x { 0 };
	int pos_y { 0 };
};

struct Gamemap {
public:
	static const int width = 20;
	static const int height = 40;
	char boardArray[width][height]{};
};

int main() {

	Gamemap* map = new Gamemap;

	// init draw game map
	for (int x = 0; x < map->width; x++) {
		for (int y = 0; y < map->height; y++) {
			map->boardArray[x][y] = '.';
		}
	}

	// draw apple
	map->boardArray[randGen(map->width)][randGen(map->height)] = '1';

	while (true)
	{
		// render screen?
		std::string buffer;

		// limiting framerate
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		// resets cursor to top left of the console window
		std::cout << "\x1b[H" << std::flush;
		// update game map
		for (int x = 0; x < map->width; x++) {
			buffer += '\n';
			for (int y = 0; y < map->height; y++) {
				buffer += map->boardArray[x][y];
			}
		}
		std::cout << buffer;
	}

	delete map;
	return 0;
}