#pragma once
#ifndef T1_TIME
#define T1_TIME

#include <string>

namespace t1
{
	class Time
	{
	private:
		static inline int currentTime = 0;
		static inline int currentWave = 0;

	public:
		static void loadTime(const std::string& folder);
		static void saveTime(const std::string& folder);

		static void resetTime();
		static void setTime(const int time);
		static void setWave(const int wave);
		static int getTime() { return currentTime; }
		static int getWave() { return currentWave; }

		static void timeRun(const int ticks);
		static void setNextWave();
	};
}

#endif // T1_TIME
