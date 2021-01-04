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

Map::Map() {
	for (int x = 0; x < Map::m_width; x++) {
		for (int y = 0; y < Map::m_height; y++) {
			Map::m_boardArray[x][y] = '.';

			// INIT BOX:
			if (x < Map::m_width / Map::m_width) {
				Map::m_boardArray[x][y] = SIDES_TOP_BOT;
			}
			if (x == Map::m_width - 1)
			{
				Map::m_boardArray[x][y] = SIDES_TOP_BOT;
			}
			if (y < Map::m_height / Map::m_height) {
				Map::m_boardArray[x][y] = SIDES_LEFT_RIGHT;
			}
			if (y == Map::m_height - 1)
			{
				Map::m_boardArray[x][y] = SIDES_LEFT_RIGHT;
			}

			// CORNERS:
			if (x < Map::m_width / Map::m_width && y < Map::m_height / Map::m_height) {
				Map::m_boardArray[x][y] = CORNER_TOP_LEFT;
			}
			if (x < Map::m_width / Map::m_width && y == Map::m_height - 1) {
				Map::m_boardArray[x][y] = CORNER_TOP_RIGHT;
			}
			if (x == Map::m_width - 1 && y < Map::m_height / Map::m_height) {
				Map::m_boardArray[x][y] = CORNER_BOT_LEFT;
			}
			if (x == Map::m_width - 1 && y == Map::m_height - 1) {
				Map::m_boardArray[x][y] = CORNER_BOT_RIGHT;
			}
		}
	}

	// check whole array if apple exists, if no then continue
	bool initApple = true;

	// INIT APPLE:
	while (initApple) {

		Map::randWidth = randGen(Map::m_width);
		Map::randHeight = randGen(Map::m_height);

		Map::apple = Map::m_boardArray[Map::randWidth][Map::randHeight];

		if (Map::apple != 'X'
			&& Map::apple != '#'
			&& Map::apple != SIDES_TOP_BOT
			&& Map::apple != SIDES_LEFT_RIGHT
			&& Map::apple != CORNER_TOP_LEFT
			&& Map::apple != CORNER_TOP_RIGHT
			&& Map::apple != CORNER_BOT_LEFT
			&& Map::apple != CORNER_BOT_RIGHT
			) {
			Map::m_boardArray[randWidth][randHeight] = 'O';
			initApple = false;
		}
	}
}

void Map::updateApple() {
	bool spawnApple = true;
}