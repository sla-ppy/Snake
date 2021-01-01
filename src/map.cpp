#include "map.h"
#include "rand.h"

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

void Map::initMap() {
	for (int x = 0; x < Map::width; x++) {
		for (int y = 0; y < Map::height; y++) {
			//map->boardArray[x][y] = '.';
			Map::boardArray[x][y] = '.';

			// BOX:
			if (x < Map::width / Map::width) {
				//map->boardArray[x][y] = SIDES_TOP_BOT;
				Map::boardArray[x][y] = SIDES_TOP_BOT;
			}
			if (x == Map::width - 1)
			{
				//map->boardArray[x][y] = SIDES_TOP_BOT;
				Map::boardArray[x][y] = SIDES_TOP_BOT;
			}
			if (y < Map::height / Map::height) {
				//map->boardArray[x][y] = SIDES_LEFT_RIGHT;
				Map::boardArray[x][y] = SIDES_LEFT_RIGHT;
			}
			if (y == Map::height - 1)
			{
				//map->boardArray[x][y] = SIDES_LEFT_RIGHT;
				Map::boardArray[x][y] = SIDES_LEFT_RIGHT;
			}

			// CORNERS:
			/*if (x < map->width / map->width && y < map->height / map->height) {
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
			}*/

			if (x < Map::width / Map::height && y < Map::height / Map::height) {
				Map::boardArray[x][y] = CORNER_TOP_LEFT;
			}
			if (x < Map::width / Map::width && y == Map::height - 1) {
				Map::boardArray[x][y] = CORNER_TOP_RIGHT;
			}
			if (x == Map::width - 1 && y < Map::height / Map::height) {
				Map::boardArray[x][y] = CORNER_BOT_LEFT;
			}
			if (x == Map::width - 1 && y == Map::height - 1) {
				Map::boardArray[x][y] = CORNER_BOT_RIGHT;
			}
		}
	}
}

void Map::initApple() {
	// draw apple
	bool findingApplePos = true;

	while (findingApplePos) {
		int width = randGen(Map::width);
		int height = randGen(Map::height);

		wchar_t  apple = Map::boardArray[width][height];

		if (apple != 'X'
			&& apple != SIDES_TOP_BOT
			&& apple != SIDES_LEFT_RIGHT
			&& apple != CORNER_TOP_LEFT
			&& apple != CORNER_TOP_RIGHT
			&& apple != CORNER_BOT_LEFT
			&& apple != CORNER_BOT_RIGHT
			) {
			Map::boardArray[width][height] = 'O';
			findingApplePos = false;
		}
	}
}