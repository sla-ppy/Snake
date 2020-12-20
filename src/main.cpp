#include <iostream>
#include <io.h> // _setmode
#include <fcntl.h> // _O_U16TEXT
#include <tchar.h> // _TCHAR*

#include "game.h"

#include <Windows.h>
int main() {
	// needed for unicode chars
	_setmode(_fileno(stdout), _O_U8TEXT);

	Game* game = new Game;

	game->init();
	game->update();
	game->deinit();

	delete game;

	return 0;
}