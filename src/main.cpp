#include <Windows.h>
#include <fcntl.h> // _O_U16TEXT
#include <io.h> // _setmode
#include <iostream>
#include <tchar.h> // _TCHAR*

#include "game.h"

// StackOverFlow: basically hides the console cursor
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main() {
    // needed for unicode chars
    _setmode(_fileno(stdout), _O_U8TEXT);

    Game game;

    ShowConsoleCursor(false);

    game.update();

    return 0;
}