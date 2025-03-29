
#include "t1_random.h"


int t1::Rand::getValue(const int min, const int max)
{
	std::uniform_int_distribution<> dist(min, max);
	return dist(generator);
}

bool t1::Rand::getChance(const int from)
{
	return getValue(0, from) == 0;
}

void t1::Rand::setSeed(uint32_t seed)
{
	Rand::seed = seed;
	generator = std::move(std::mt19937(seed));
}
