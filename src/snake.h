#ifndef SNAKE_H
#define SNAKE_H

struct Snake {
public:
	int pos_x{ 0 };
	int pos_y{ 0 };

	int* posXPtr = &pos_x;
	int* posYPtr = &pos_y;
};

#endif // !SNAKE_H