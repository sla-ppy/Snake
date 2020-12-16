// NOTE: game.cpp encoding was set to

#include <iostream>
#include <thread>

#include "game.h"
#include "rand.h"

struct Gamemap {
public:
	static const int width = 20; //3;
	static const int height = 40; //3;
	// wchar_t - maybe for the UNICODE characters
	// char
	wchar_t boardArray[width][height]{};
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
				map->boardArray[x][y] = L'\u2550';
			}
			// bottom side
			if (x == map->width -1 )
			{
				map->boardArray[x][y] = L'\u2550';
			}
			// left side
			if (y < map->height / map->height) {
				map->boardArray[x][y] = L'\u2551';
			}
			// right side
			if (y == map->height - 1)
			{
				map->boardArray[x][y] = L'\u2551';
			}

			// CORNERS:
			// top-left
			if (x < map->width / map->width && y < map->height / map->height) {
				map->boardArray[x][y] = L'\u2554';
			}
			// top-right
			if (x < map->width / map->width && y == map->height - 1) {
				map->boardArray[x][y] = L'\u2557';
			}
			// bottom-left
			if (x == map->width - 1 && y < map->height / map->height) {
				map->boardArray[x][y] = L'\u255A';
			}
			// bottom-right
			if (x == map->width - 1 && y == map->height - 1) {
				map->boardArray[x][y] = L'\u255D';
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

		int width = randGen(map->width);
		int height = randGen(map->height);

		// char
		wchar_t apple = map->boardArray[width][height];

		// ALT + SHIFT does stuff, interesting stuffffff!!! dont forget lol

		// FIXME: collision is now all whacky because of the extended ASCII table values, unsure why this isn't working!
		if (apple != 'X' // this is a clear example that ascii number table wont be a solution here, because instead of 'XYZ' number, the ASCII character is recorded as something else like 'Í' in this case!
			&& apple != L'\u2550' //186  //'ş'
			&& apple != L'\u2551' //205  //'Č'	
			&& apple != L'\u2554' //201  //'Ľ'
			&& apple != L'\u2557' //200  //'»'
			&& apple != L'\u255A' //187  //'É'
			&& apple != L'\u255D' //188  //'X'
			) {
			map->boardArray[width][height] = 'O';
			findingApplePos = false;
		}
	}
}

void Game::update() {
	while (true)
	{
		// double buffering: reference in book
		// std::string - changed this to adopt the unicode
		std::wstring buffer;

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
		// std::cout - changed this to adopt the unicode
		std::wcout << buffer;
	}
}

void Game::deinit() {
	delete map;
}