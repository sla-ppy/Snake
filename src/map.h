#ifndef MAP_H
#define MAP_H

struct Map {
	static const int m_width = 20; //3;
	static const int m_height = 40; //3;
	wchar_t m_boardArray[m_width][m_height];

	int randWidth { 0 };
	int randHeight { 0 };

	wchar_t apple;

	Map();

	void spawnApple();
};

#endif // !MAP_H