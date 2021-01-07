#include <iostream>
#include <thread>
#include <Windows.h>

#include "map.h"
#include "game.h"
#include "snake.h"

// declaring the game objects here

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
	else if (GetAsyncKeyState(VK_SPACE)) {
		// debug apple spawning
		map->spawnApple();
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
		std::wcout << sHead->pos_x;
		break;
	case Direction::DOWN:
		sHead->pos_x++;
		std::wcout << sHead->pos_x;
		break;
	case Direction::LEFT:
		sHead->pos_y--;
		std::wcout << sHead->pos_y;
		break;
	case Direction::RIGHT:
		sHead->pos_y++;
		std::wcout << sHead->pos_y;
		// this is terrible
		{int current_pos_y2 = sHead->pos_y;
		current_pos_y2 -= sHead->pos_y++;
		std::wcout << current_pos_y2;}
		break;
	}
}


// taken from slappy-test, might be the way to go
//Snake* sCells{ nullptr };
//size_t cell_count{ 5 };
//
//sCells = new Snake[cell_count];
//
//void resize_asteroids_to(size_t new_size) {
//	Snake* new_cells = new Snake[new_size];
//	for (size_t i = 0; i < cell_count; ++i) {
//		new_cells[i] = sCells[i];
//	}
//	delete[] sCells;
//	sCells = new_cells;
//	cell_count = new_size;
//}

Game::Game() {
	map = new Map;
	sHead = new Snake;

	// INIT SNAKE:
	sHead->pos_x = map->m_width / 2;
	sHead->pos_y = map->m_height / 2;

	// RENDER SNAKE
	map->m_boardArray[sHead->pos_x][sHead->pos_y] = 'X';
}

void Game::update() {
	Direction dir = Direction::NOTMOVING;

	while (true)
	{
		// double buffering
		std::wstring buffer;

		// limiting framerate
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		// sets cursor position back to the "home" position
		std::wcout << "\x1b[H" << std::flush;

		// illusion of movement 1/2
		map->m_boardArray[sHead->pos_x][sHead->pos_y] = '.';

		// MOVEMENT:
		inputCheck(dir);
		doMovement(dir);

		// COLLISION:
		if (sHead->pos_x <= 0
			|| sHead->pos_y <= 0
			|| sHead->pos_x >= (map->m_width - 1)
			|| sHead->pos_y >= (map->m_height - 1)) {
			break;
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

		// render snake cells
		//for (int i = 0; i < sCells[i]; i++) {
		//	map->m_boardArray[sCells[i]->pos_x][sCells[i]->pos_y] = '#';
		//}

		// update game map
		for (int x = 0; x < map->m_width; x++) {
			buffer += '\n';
			for (int y = 0; y < map->m_height; y++) {
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
}