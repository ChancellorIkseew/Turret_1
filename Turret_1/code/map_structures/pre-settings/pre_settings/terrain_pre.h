#pragma once
#ifndef MAP_STR_TERRAIN_PRE_H
#define MAP_STR_TERRAIN_PRE_H

#include <map>

#include "map_structures/base_engine/base_engine.h"


struct TerrainPre
{
	uint32_t seed;
	uint8_t smoothLayer;
	std::map<int, int> frequency;
	std::map<int, int> depositSize;
	TileCoord mapSize;
};

#endif // MAP_STR_TERRAIN_PRE_H
