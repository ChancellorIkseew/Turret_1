#pragma once
#ifndef T1_PATH_FINDING_H
#define T1_PATH_FINDING_H

#include "map_structures/base_engine/base_engine.h"

class Entity;
class BuildingsMap;
class BlueprintsMap;

class PathFinding
{
public:
	static TileCoord findNextTile(const TileCoord point, const TileCoord aim, const BuildingsMap& buildingsMap);
	static TileCoord findClosestCore(const TileCoord point, const BuildingsMap& buildingsMap);
	static TileCoord findClosestBlueprint(const TileCoord point, const BlueprintsMap& blueprintsMap);
};

#endif // T1_PATH_FINDING_H
