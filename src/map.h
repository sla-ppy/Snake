#ifndef MAP_H
#define MAP_H

struct Map {
	static const int width = 20; //3;
	static const int height = 40; //3;
	wchar_t boardArray[width][height];

public:
	Map() {};
	~Map() {};

	void initMap();
	void initApple();
};

#endif // !MAP_H