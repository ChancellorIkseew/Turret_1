
#include "t1_random.h"


int t1::Rand::getValue(const int min, const int max)
{
	std::uniform_int_distribution<> dist(min, max);
	return dist(generator);
}

void t1::Rand::setSeed(uint32_t seed)
{
	Rand::seed = seed;
	generator = std::move(std::mt19937(seed));
}
