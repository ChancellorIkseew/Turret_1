
#include "t1_time.h"


void t1::Time::save(cereal::BinaryOutputArchive& archive) const {
	archive(currentTime, currentWave);
}
void t1::Time::load(cereal::BinaryInputArchive& archive) {
	archive(currentTime, currentWave);
}

void t1::Time::resetTime() {
	currentTime = 0;
	currentWave = 0;
}

void t1::Time::setTime(const int time) {
	currentTime = time;
}
void t1::Time::setWave(const int wave) {
	currentWave = wave;
}

void t1::Time::timeRun(const int ticks) {
	currentTime += ticks;
}
void t1::Time::setNextWave() {
	++currentWave;
}
