#include <iostream>
#include <thread>
#include <Windows.h>

#include "map.h"
#include "game.h"

struct SnakeNode {
public:
	int pos_x{ 0 };
	int pos_y{ 0 };
};

struct SnakeHead : SnakeNode {
};

// MASSIVE TODO: use RAII everywhere

// declaring the game objects here
SnakeHead* sHead { nullptr };
Map* map { nullptr };

void Game::init() {

	map = new Map;
	sHead = new SnakeHead;

	// INIT SNAKE:
	sHead->pos_x = map->m_width / 2;
	sHead->pos_y = map->m_height / 2;

	// RENDER SNAKE
	map->Map::m_boardArray[sHead->pos_x][sHead->pos_y] = 'X';
}

enum class Direction {
	NOTMOVING,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

void Game::update() {
	Direction dir = Direction::NOTMOVING;

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
		map->Map::m_boardArray[sHead->pos_x][sHead->pos_y] = '.';

		// MOVEMENT:
		// FIXME: movement still needs attention
		// Example: If we go up, we cant go down aka "reversing" cant happen.

		// input handling part of the program
		if (GetAsyncKeyState(VK_UP)) {
			dir = Direction::UP;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			dir = Direction::DOWN;
		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			dir = Direction::LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			dir = Direction::RIGHT;
		}
		else if (GetAsyncKeyState(VK_SPACE)) {
			// debug apple spawning
			std::wcout << "Space";
			map->Map::updateApple();

		}
		else {
			dir = dir; // dir stays the same
		}

		// actual movement
		switch (dir) {
		case Direction::UP:
			sHead->pos_x--;
			break;
		case Direction::DOWN:
			sHead->pos_x++;
			break;
		case Direction::LEFT:
			sHead->pos_y--;
			break;
		case Direction::RIGHT:
			sHead->pos_y++;
			break;
		}

		// not sure if this would work
		if (sHead->pos_x == map->apple || sHead->pos_y == map->apple) {
			std::wcout << "Apple hit" << std::endl;
		}

		// wont work like this
		if (sHead->pos_x == 'O' || sHead->pos_y == 'O') {
			std::wcout << "Apple hit." << std::endl;
			// spawn apple here
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
		if (sHead->pos_x == (map->m_width / map->m_width) - 1 || sHead->pos_y == (map->m_height / map->m_height) - 1) {
			break;
		}

		// bottom and right
		if (sHead->pos_x == (map->m_width - 1) || sHead->pos_y == (map->m_height - 1)) {
			break;
		}

		// illusion of movement 2/2
		// render position of new 'X'
		map->Map::m_boardArray[sHead->pos_x][sHead->pos_y] = 'X';

		// update game map
		for (int x = 0; x < map->m_width; x++) {
			buffer += '\n';
			for (int y = 0; y < map->m_height; y++) {
				buffer += map->Map::m_boardArray[x][y];
			}
		}
		std::wcout << buffer;
	}
	
	std::wcout << "You've died." << std::endl;
	// just so the error message doesn't ruin our map after game over
	for (int i = 0; i < 20; i++) {
		std::wcout << "\n";
	}
}

void Game::deinit() {
	delete map;
	delete sHead;
}