#pragma once
#ifndef T1_RANDOM_H
#define T1_RANDOM_H

#include <random>

namespace t1
{
	class Rand
	{
	public:
		static int getValue(const int min, const int max);
		static bool getChance(const int from);
		static void setSeed(const uint32_t value);
	};
}

#endif // T1_RANDOM_H
