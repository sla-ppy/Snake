#include <iostream>
#include <thread>
#include <Windows.h>

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

	// TOP_BOT & LEFT_RIGHT are the same symbol, thats why they aren't stored seperately
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

		if (apple != 'X'
			&& apple != SIDES_TOP_BOT
			&& apple != SIDES_LEFT_RIGHT
			&& apple != CORNER_TOP_LEFT
			&& apple != CORNER_TOP_RIGHT
			&& apple != CORNER_BOT_LEFT
			&& apple != CORNER_BOT_RIGHT
			) {
			map->boardArray[width][height] = 'O';
			findingApplePos = false;
		}
	}
}

void Game::update() {
	while (true)
	{
		// buffering
		// TODO: could improve by implementing double buffering, which might solve the blinking issue so i wouldn't have to disable the cursor
		std::wstring buffer;

		// limiting framerate
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		// sets cursor position back to the "home" position
		std::wcout << "\x1b[H" << std::flush;

		// illusion of movement 1/2
		// also turned out to be a clever solution to enable the apple spawning to continue, since missing the 'O' character from the array would mean we dont have any spawned yet.
		map->boardArray[sHead->pos_x][sHead->pos_y] = '.';

		// MOVEMENT:
		// FIXME: movement still needs attention
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
		// also probaly a decent way to deal with collision, because even corners are handled this way, since both if's will be true if snek would somehow manage to get on the corner tile.
		// top and left
		if (sHead->pos_x == (map->width / map->width) -1 || sHead->pos_y == (map->height / map->height) -1) {
			return;
		}
		// bottom and right
		if (sHead->pos_x == (map->width -1) || sHead->pos_y == (map->height -1)) {
			return;
		}

		// illusion of movement 2/2
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