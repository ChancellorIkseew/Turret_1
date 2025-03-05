#pragma once
#ifndef T1_ENT_PATH_FINDING_H
#define T1_ENT_PATH_FINDING_H

#include "map_structures/base_engine/base_engine.h"

class Entity;
class BuildingsMap;

class PathFinding
{
public:
	static TileCoord findNextTile(const TileCoord point, const TileCoord aim, const BuildingsMap& buildingsMap);
	static TileCoord findClosestCore(const TileCoord point, const BuildingsMap& buildingsMap);
};

#endif // T1_ENT_PATH_FINDING_H
