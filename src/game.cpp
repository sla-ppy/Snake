// NOTE: game.cpp encoding was set to UTF-8

#include <iostream>
#include <thread>
#include <Windows.h> // for keystrokes

#include "game.h"
#include "rand.h"

struct Gamemap {
public:
	static const int width = 20; //3;
	static const int height = 40; //3;
	wchar_t boardArray[width][height]{};
};

struct SnakeNode {
public:
	int pos_x{ 0 };
	int pos_y{ 0 };
};

struct SnakeHead : SnakeNode {

};

Gamemap* map = new Gamemap;
SnakeHead* sHead = new SnakeHead;

void Game::init() {

	// top_bot & left_right are the same symbol, thats why they aren't stored seperately
	enum boxEnum {
		SIDES_TOP_BOT = L'\u2550',
		SIDES_LEFT_RIGHT = L'\u2551',
		CORNER_TOP_LEFT = L'\u2554',
		CORNER_TOP_RIGHT = L'\u2557',
		CORNER_BOT_LEFT = L'\u255A',
		CORNER_BOT_RIGHT = L'\u255D'
	};

	for (int x = 0; x < map->width; x++) {
		for (int y = 0; y < map->height; y++) {
			map->boardArray[x][y] = '.';

			// BOX:
			if (x < map->width / map->width) {
				map->boardArray[x][y] = SIDES_TOP_BOT;
			}
			if (x == map->width - 1)
			{
				map->boardArray[x][y] = SIDES_TOP_BOT;
			}
			if (y < map->height / map->height) {
				map->boardArray[x][y] = SIDES_LEFT_RIGHT;
			}
			if (y == map->height - 1)
			{
				map->boardArray[x][y] = SIDES_LEFT_RIGHT;
			}

			// CORNERS:
			if (x < map->width / map->width && y < map->height / map->height) {
				map->boardArray[x][y] = CORNER_TOP_LEFT;
			}
			if (x < map->width / map->width && y == map->height - 1) {
				map->boardArray[x][y] = CORNER_TOP_RIGHT;
			}
			if (x == map->width - 1 && y < map->height / map->height) {
				map->boardArray[x][y] = CORNER_BOT_LEFT;
			}
			if (x == map->width - 1 && y == map->height - 1) {
				map->boardArray[x][y] = CORNER_BOT_RIGHT;
			}

			// SNAKE:
			// head
			sHead->pos_x = map->width / 2;
			sHead->pos_y = map->height / 2;
			// render sHead
			map->boardArray[sHead->pos_x][sHead->pos_y] = 'X';
		}
	}

	// draw apple
	bool findingApplePos = true;

	while (findingApplePos) {

		int width = randGen(map->width);
		int height = randGen(map->height);

		wchar_t  apple = map->boardArray[width][height];

		// ALT + SHIFT does stuff, interesting stuffffff!!! dont forget lol

		if (apple != 'X' // this is a clear example that ascii number table wont be a solution here, because instead of 'XYZ' number, the ASCII character is recorded as something else like 'Í' in this case!
			&& apple != SIDES_TOP_BOT //186  //'ş'
			&& apple != SIDES_LEFT_RIGHT //205  //'Č'
			&& apple != CORNER_TOP_LEFT //201  //'Ľ'
			&& apple != CORNER_TOP_RIGHT //200  //'»'
			&& apple != CORNER_BOT_LEFT //187  //'É'
			&& apple != CORNER_BOT_RIGHT //188  //'X'
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
		std::wstring buffer;

		// limiting framerate
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		// FIXME: cursor keeps blinking randomly throughout the gamemap
		std::wcout << "\x1b[H" << std::flush;

		// illusion of movement
		map->boardArray[sHead->pos_x][sHead->pos_y] = '.';

		// 1. GetAsyncKeyState - for dungeon crawl
		// 2. changing else-if to if will allow us to move diagonally too, which we dont want in this case

		if (GetKeyState(VK_UP))
		{
			sHead->pos_x--;
		}
		else if (GetKeyState(VK_DOWN))
		{
			sHead->pos_x++;
		}
		else  if (GetKeyState(VK_LEFT))
		{
			sHead->pos_y--;
		}
		else  if (GetKeyState(VK_RIGHT))
		{
			sHead->pos_y++;
		}

		// COLLISION:
		// TODO: still needs snek collision for when it curls into itself
		// top and left
		if (sHead->pos_x == (map->width / map->width) -1 || sHead->pos_y == (map->height / map->height) -1) {
			return;
		}
		// bottom and right
		if (sHead->pos_x == (map->width -1) || sHead->pos_y == (map->height -1)) {
			return;
		}

		// render position of new 'X'
		map->boardArray[sHead->pos_x][sHead->pos_y] = 'X';

		// update game map
		for (int x = 0; x < map->width; x++) {
			buffer += '\n';
			for (int y = 0; y < map->height; y++) {
				buffer += map->boardArray[x][y];
			}
		}
		std::wcout << buffer;
	}
}

void Game::deinit() {
	delete map;
}