#include <iostream>
#include <thread>
#include <Windows.h>

#include "map.h"
#include "game.h"
#include "snake.h"

void Game::inputCheck(Direction& dir) {
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
	else {
		dir = dir; // dir stays the same
	}
}

void Game::doMovement(Direction& dir) {
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
}

Game::Game() {
	map = new Map;
	sHead = new Snake;
	apple = new Apple;

	// INIT SNAKE:
	sHead->pos_x = map->width / 2;
	sHead->pos_y = map->height / 2;

	// RENDER SNAKE:
	map->m_boardArray[sHead->pos_x][sHead->pos_y] = 'X';

	// APPLE:
	// FIXME: apple spawning is wrong, because its able to spawn outside of our playfield, possibly a -1, -1 issue of going over the limit
	if (map->m_boardArray[apple->randPosX][apple->randPosY] == '.') {
		map->m_boardArray[apple->randPosX][apple->randPosY] = 'O';
	}
}

void Game::update() {
	Direction dir = Direction::NOTMOVING;

	while (true)
	{
		// DOUBLE BUFFER:
		std::wstring buffer;

		// LIMIT FRAMERATE:
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		// sets cursor position back to the "home" position
		std::wcout << "\x1b[H" << std::flush;

		// illusion of movement 1/2
		map->m_boardArray[sHead->pos_x][sHead->pos_y] = '.';

		// MOVEMENT:
		inputCheck(dir);
		doMovement(dir);

		// WALL COLLISION:
		if (sHead->pos_x <= 0
			|| sHead->pos_y <= 0
			|| sHead->pos_x >= (map->width - 1)
			|| sHead->pos_y >= (map->height - 1)) {
			break;
		}

		// APPLE COLLISION:
		if (sHead->pos_x == apple->randPosX && sHead->pos_y == apple->randPosY) {
			std::wcout << "Apple hit.";
			map->m_boardArray[apple->randPosX][apple->randPosY] = '.';

			apple->genApplePos();
			if (map->m_boardArray[apple->randPosX][apple->randPosY] == '.') {
				map->m_boardArray[apple->randPosX][apple->randPosY] = 'O';
			}
		}

		/*
		TODO:
		I. snake body:
			1. sCells[i]++ when apple is hit
			2. assign new cell to the previous cell's previous location
			3. make cell follow the next cell's previous location each frame
			4. render sCells as a whole
		II. check if needed: movement reversing issue
		III. FIXME: sometimes apple doesn't spawn when game is init
		*/

		// illusion of movement 2/2
		// render position of new 'X'
		map->m_boardArray[sHead->pos_x][sHead->pos_y] = 'X';

		// update game map
		for (int x = 0; x < map->width; x++) {
			buffer += '\n';
			for (int y = 0; y < map->height; y++) {
				buffer += map->m_boardArray[x][y];
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

Game::~Game() {
	delete map;
	delete sHead;
	delete apple;
}