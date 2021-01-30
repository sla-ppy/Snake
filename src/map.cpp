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
    // INIT BOX:
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            wchar_t tile = '.';

            // TOP BOTTOM:
            if (x < 1) {
                tile = SIDES_TOP_BOT;
            } else if (x == width - 1) {
                tile = SIDES_TOP_BOT;
            }
            // LEFT RIGHT:
            if (y < 1) {
                tile = SIDES_LEFT_RIGHT;
            } else if (y == height - 1) {
                tile = SIDES_LEFT_RIGHT;
            }

            // CORNERS:
            if (x < 1 && y < 1) {
                tile = CORNER_TOP_LEFT;
            } else if (x < 1 && y == height - 1) {
                tile = CORNER_TOP_RIGHT;
            } else if (x == width - 1 && y < 1) {
                tile = CORNER_BOT_LEFT;
            } else if (x == width - 1 && y == height - 1) {
                tile = CORNER_BOT_RIGHT;
            }
            m_boardArray[x][y] = tile;
        }
    }
}

Apple::Apple() {
    genApplePos();
}

void Apple::genApplePos() {
    randPosX = randGen(Map::width);
    randPosY = randGen(Map::height);
}