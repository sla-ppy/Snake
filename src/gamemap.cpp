#include "gamemap.h"

// CONTINUE: from here
void Gamemap::draw() {
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
		}
	}
}