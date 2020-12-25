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
public:
	void move() {

	}
};

Gamemap* map = new Gamemap;
SnakeHead* sHead = new SnakeHead;

void Game::init() {
	// TOP_BOT & LEFT_RIGHT are the same symbol, thats why they aren't stored seperately
	enum boxEnum {
		// POLISH: alternate way to rendering box is by using win console api, and drawing with the graphical lines it provides.
		//https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
		//https://vt100.net/docs/vt220-rm/table2-4.html
		// dot: "there's also the console screen buffer API with which you can "draw" character directly into the 2d screen buffer of the console"
		// dot: "and if you're already going to be using non-standard stuff, might as well just go straight to the source"
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

enum Direction {
	NOTMOVING,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

void Game::update() {
	Direction dir = NOTMOVING;
	while (true)
	{
		// buffering
		// TODO: could improve by implementing double buffering, which might solve the blinking issue so i wouldn't have to disable the cursor
		std::wstring buffer;

		// limiting framerate
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		// sets cursor position back to the "home" position
		std::wcout << "\x1b[H" << std::flush;

		// illusion of movement 1/2
		// also turned out to be a clever solution to enable the apple spawning to continue, since missing the 'O' character from the array would mean we dont have any spawned yet.
		map->boardArray[sHead->pos_x][sHead->pos_y] = '.';

		// MOVEMENT:
		// FIXME: movement still needs attention
		// Example: If we go up, we cant go down aka "reversing" cant happen.

		// input handling part of the program
		if (GetAsyncKeyState(VK_UP)) {
			dir = UP;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			dir = DOWN;
		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			dir = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			dir = RIGHT;
		}
		else {
			dir = dir; // dir stays the same
		}

		switch (dir) {
		case UP:
			sHead->pos_x--;
			break;
		case DOWN:
			sHead->pos_x++;
			break;
		case LEFT:
			sHead->pos_y--;
			break;
		case RIGHT:
			sHead->pos_y++;
			break;
		}

		/*
		TODO:
		1. the snek collision, which shouldn't be too challenging, given any cell's value is "#", we got collision
		2. implementing my method of how the snake should move, node objects which point to the previous node's position, kinda like a linked list actually (yes i rly like this word)
		3. making appleh spawn again when its value got set back to '.' so i'll need to find a way to figure out if one of the cell's value is set to 'O' or no
		4. polish!
		*/

		// COLLISION:
		// TODO: still needs snek collision for when it curls into itself
		// also probaly a decent way to deal with collision, because even corners are handled this way, since both if's will be true if snek would somehow manage to get on the corner tile.
		// top and left
		if (sHead->pos_x == (map->width / map->width) - 1 || sHead->pos_y == (map->height / map->height) - 1) {
			break;
		}

		// bottom and right
		if (sHead->pos_x == (map->width - 1) || sHead->pos_y == (map->height - 1)) {
			break;
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