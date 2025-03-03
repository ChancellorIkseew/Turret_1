
#include "sleep.h"
#include <chrono>
#include <thread>

void t1::system::sleep(const int timeInMilliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(timeInMilliseconds));
}