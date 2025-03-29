#pragma once
#ifndef T1_RANDOM_H
#define T1_RANDOM_H

#include <random>

namespace t1
{
	class Rand
	{
	private:
		static inline uint32_t seed = 0;
		static inline std::mt19937 generator = std::mt19937(0);

	public:
		static int getValue(const int min, const int max);
		static bool getChance(const int from);
		static void setSeed(uint32_t seed);
		static uint32_t getSeed() { return seed; }

	};
}

#endif // T1_RANDOM_H
