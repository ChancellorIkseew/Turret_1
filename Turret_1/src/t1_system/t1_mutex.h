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
	///@brief Locks all drawing. Is needed for texturepacks reload.
	inline std::mutex drawing;
}

#endif // T1_MUTEX
