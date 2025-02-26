#pragma once
#ifndef T1_TIME
#define T1_TIME

#include <cereal/archives/binary.hpp>

namespace t1
{
	class Time
	{
	private:
		int currentTime = 0;
		int currentWave = 0;

	public:
		Time() = default;
		~Time() = default;

		void save(cereal::BinaryOutputArchive& archive) const;
		void load(cereal::BinaryInputArchive& archive);

		void resetTime();
		void setTime(const int time);
		void setWave(const int wave);
		int getTime() const { return currentTime; }
		int getWave() const { return currentWave; }

		void timeRun(const int ticks);
		void setNextWave();
	};
}

#endif // T1_TIME
