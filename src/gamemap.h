#ifndef GAMEMAP_H
#define GAMEMAP_H

struct Gamemap {
public:
	static const int width = 20; //3;
	static const int height = 40; //3;
	// wchar_t - maybe for the UNICODE characters
	// char
	wchar_t boardArray[width][height]{};

	void draw();
};

#endif // !GAMEMAP_H