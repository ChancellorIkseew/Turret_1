#pragma once
#ifndef MAP_STR_TIMER_PRE_H
#define MAP_STR_TIMER_PRE_H

#include <map>

#include "map_structures/base_engine/tile_coord.h"


struct TimerPre
{
	uint32_t firstWave;
	uint32_t normalWave;
	uint32_t bossWave;
};

#endif // MAP_STR_TIMER_PRE_H
