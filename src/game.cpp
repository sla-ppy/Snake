// NOTE: game.cpp encoding was set to UTF-8

#include <iostream>
#include <thread>
#include <Windows.h> // for keystrokes
#include <conio.h> // getch()

#include "game.h"
#include "rand.h"

#define WM_CHAR 0x0102
#define WM_KEYDOWN 0x0100
#define VK_UP 0x26
#define VK_DOWN 0x28
#define VK_LEFT 0x25
#define VK_RIGHT 0x27

struct Gamemap {
public:
	static const int width = 20; //3;
	static const int height = 40; //3;
	// wchar_t - maybe for the UNICODE characters
	// char
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
			if (x == map->width - 1)
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
		// was 100ms - but i changed it to 1000ms after i switched from ASCII to UNICODE
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		// resets cursor to top left of the console window
		// FIXME: cursor keeps blinking randomly throughout the gamemap
		std::wcout << "\x1b[H" << std::flush;

		bool isMoving = false;

		// TODO: continue from here
		  case WM_KEYDOWN:
			  switch (wParam)
			  {
			  case VK_LEFT:
				  // Process the LEFT ARROW key.
				  break;
			  case VK_RIGHT:
				  // Process the RIGHT ARROW key. 
				  break;
			  case VK_UP:
				  // Process the UP ARROW key. 
				  break;
			  case VK_DOWN:
				  // Process the DOWN ARROW key. 
				  break;
			  default:
				  break;
			  }

			  sHead->pos_x--;
			  sHead->pos_y++;

			  // render new 'X'
			  // TODO: we also have to delete the previous 'X', wich gives us the illusion of movement
			  map->boardArray[sHead->pos_x][sHead->pos_y] = 'X';

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