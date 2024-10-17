#pragma once
#ifndef MAP_STR_TERRAIN_PRE_H
#define MAP_STR_TERRAIN_PRE_H

#include <map>


class TerrainPre
{
public:
	static inline uint32_t seed;
	static inline uint8_t smoothLayer;
	static inline std::map<int, int> frequency;
	static inline std::map<int, int> depositSize;

};

#endif // MAP_STR_TERRAIN_PRE_H
