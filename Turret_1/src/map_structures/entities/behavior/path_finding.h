#pragma once
#ifndef T1_ENT_PATH_FINDING_H
#define T1_ENT_PATH_FINDING_H

#include "map_structures/base_engine/base_engine.h"

class Entity;
class BuildingsMap;

namespace t1::ent
{
	TileCoord findDestination(const Entity& entity, const BuildingsMap& buildingsMap);
	TileCoord findClosestCore(const Entity& entity, const BuildingsMap& buildingsMap);
}

#endif // T1_ENT_PATH_FINDING_H
