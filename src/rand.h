#ifndef RAND_H
#define RAND_H

#include <random>

static inline std::random_device rd;
static inline std::mt19937 gen(rd());

int randGen(int max)
{
	std::uniform_int_distribution<> distrib(0, max - 1); // Here is where you can change the MIN and MAX values of the random dib.	

	int randResult = distrib(gen);
	return randResult;
}

#endif // RAND_H