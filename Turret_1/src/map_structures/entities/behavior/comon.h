#pragma once
#ifndef T1_COMON_BEHAVIOR_H
#define T1_COMON_BEHAVIOR_H

#include "map_structures/base_engine/base_engine.h"

class BuildingsMap;

class Comon
{
public:
	static TileCoord findDirectPahtNextTile(const PixelCoord point, const TileCoord currentTile, const float angleToAim);
};

#endif // T1_COMON_BEHAVIOR_H
