#ifndef MAP_H
#define MAP_H

struct Map {
	static const int width = 20; //3;
	static const int height = 40; //3;
	wchar_t m_boardArray[width][height];

	Map();
};

struct Apple {
	int randPosX{ 0 };
	int randPosY{ 0 };

	wchar_t apple;

	Apple();

	void genApplePos();
};
#endif // !MAP_H