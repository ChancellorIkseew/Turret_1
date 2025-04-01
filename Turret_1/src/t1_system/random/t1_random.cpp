
#include "t1_random.h"

static uint32_t seed = 0;
static std::mt19937 generator = std::mt19937(0);

int t1::Rand::getValue(const int min, const int max)
{
	std::uniform_int_distribution<> dist(min, max);
	return dist(generator);
}

bool t1::Rand::getChance(const int from)
{
	return getValue(0, from) == 0;
}

void t1::Rand::setSeed(const uint32_t value)
{
	seed = value;
	generator.seed(seed);
}
