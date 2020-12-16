#include <iostream>
#include <io.h> // _setmode
#include <fcntl.h> // _O_U16TEXT
#include <tchar.h> // _TCHAR*

#include "game.h"

int main(int argc, _TCHAR* argv[]) {
	// NOTE: if we set the output to this mode, we can only use:
	// wprintf - for output instead of printf!
	_setmode(_fileno(stdout), _O_U16TEXT);

	Game* game = new Game;

	game->init();
	game->update();
	game->deinit();

	delete game;
	
	return 0;
}