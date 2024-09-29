#pragma once
#ifndef T1_TIME
#define T1_TIME

#include <string>

namespace t1::time
{
	extern int time;
	extern int waveNumber;

	void loadTime(const std::string& folder);
	void saveTime(const std::string& folder);
}

#endif // T1_TIME
