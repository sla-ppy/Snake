#include <iostream>
#include <io.h> // _setmode
#include <fcntl.h> // _O_U16TEXT
#include <tchar.h> // _TCHAR*
#include <Windows.h>

#include "game.h"

// StackOverFlow: basically hides the console cursor
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main() {
	// needed for unicode chars
	_setmode(_fileno(stdout), _O_U8TEXT);

	Game* game = new Game;

	ShowConsoleCursor(false);

	game->init();
	game->update();
	game->deinit();

	std::wcout << "You've died." << std::endl;

	delete game;

	return 0;
}