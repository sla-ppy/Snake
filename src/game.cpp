#include <iostream>
#include <thread>

#include "game.h"
#include "rand.h"

struct Gamemap {
public:
	static const int width = 3; //20;
	static const int height = 3; //40;
	// unsigned char so we are able to access the extended ASCII table and have cute "graphics"
	unsigned char boardArray[width][height]{};
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
			// BOX:
			// top side
			if (x < map->width / map->width) {
				map->boardArray[x][y] = 205;
			}
			// bottom side
			if (x == map->width -1 )
			{
				map->boardArray[x][y] = 205;
			}
			// left side
			if (y < map->height / map->height) {
				map->boardArray[x][y] = 186;
			}
			// right side
			if (y == map->height - 1)
			{
				map->boardArray[x][y] = 186;
			}

			// CORNERS:
			// top-left
			if (x < map->width / map->width && y < map->height / map->height) {
				map->boardArray[x][y] = 201;
			}
			// top-right
			if (x < map->width / map->width && y == map->height - 1) {
				map->boardArray[x][y] = 187;
			}
			// bottom-left
			if (x == map->width - 1 && y < map->height / map->height) {
				map->boardArray[x][y] = 200;
			}
			// bottom-right
			if (x == map->width - 1 && y == map->height - 1) {
				map->boardArray[x][y] = 188;
			}


			// SNAKE:
			// snake head spawn
			if (x == map->width / 2 && y == map->height / 2) {
				map->boardArray[x][y] = 'X';
			}
		}
	}

	// draw apple
	bool findingApplePos = true;

	while (findingApplePos) {

		int widthValue = randGen(map->width);
		int heightValue = randGen(map->height);

		char apple = map->boardArray[widthValue][heightValue];

		if (apple == '.') {
			apple = map->boardArray[widthValue][heightValue];
		}


		// FIXME: collision is now all whacky because of the extended ASCII table values, unsure why this isn't working!
		if (apple != 'X' // this is a clear example that ascii number table wont be a solution here, because instead of 'XYZ' number, the ASCII character is recorded as something else like 'Í' in this case!
			&& apple != 186  //'º'
			&& apple != 205  //'È'
			&& apple != 201  //'¼'
			&& apple != 200  //'»'
			&& apple != 187  //'É'
			&& apple != 188  //'X'
			) {
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