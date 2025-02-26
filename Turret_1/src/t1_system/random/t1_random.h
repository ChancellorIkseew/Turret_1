#pragma once
#ifndef T1_RANDOM_H
#define T1_RANDOM_H

#include <random>

namespace t1
{
	class Rand
	{
	private:
		static inline uint32_t seed;
		static inline std::mt19937 generator;

	public:
		static int getValue(const int min, const int max);
		static void setSeed(uint32_t seed);
		static uint32_t getSeed() { return seed; }

	};
}

#endif // T1_RANDOM_H
