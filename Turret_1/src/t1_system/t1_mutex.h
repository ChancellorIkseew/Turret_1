#pragma once
#ifndef T1_MUTEX
#define T1_MUTEX

#include <mutex>

namespace t1::system::mt
{
	inline std::mutex terrain;
	inline std::mutex buildings;
	inline std::mutex mobs;
	inline std::mutex shells;
	inline std::mutex particles;
}

#endif // T1_MUTEX
