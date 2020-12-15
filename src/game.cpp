#include <iostream>
#include <thread>

#include "Game.h"
#include "rand.h"

struct Gamemap {
public:
	static const int width = 20;
	static const int height = 40;
	char boardArray[width][height]{};
};

struct Node {
public:
	int pos_x{ 0 };
	int pos_y{ 0 };
};

Gamemap* map = new Gamemap;

void Game::init() {
	// draw game map
	for (int x = 0; x < map->width; x++) {
		for (int y = 0; y < map->height; y++) {
			map->boardArray[x][y] = '.';
			// TODO: other sides
			// draw upper line
			for (int x = 0; x < map->width / 20; x++) {
				map->boardArray[x][y] = '_';
			}
			// draw left line
			for (int y = 0; y < map->height / 40; y++) {
				map->boardArray[x][y] = '|';
			}
			// top left corner
			for (int x = 0; x < map->width / 20; x++) {
				for (int y = 0; y < map->height / 40; y++) {
					map->boardArray[x][y] = ' ';
				}
			}
		}
	}

	// draw apple
	bool findingApplePos = true;

	while (findingApplePos) {

		int widthValue = randGen(map->width);
		int heightValue = randGen(map->height);

		char apple = map->boardArray[widthValue][heightValue];

		if (apple != '_' && apple != '|' && apple != ' ' && apple != '#' && apple != 'X') {
			map->boardArray[widthValue][heightValue] = 'O';
			findingApplePos = false;
		}
	}
}

void Game::update() {
	while (true)
	{
		// double buffering: reference in book
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
}

void Game::deinit() {
	delete map;
}