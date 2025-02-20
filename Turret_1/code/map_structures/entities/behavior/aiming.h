#pragma once
#ifndef T1_ENT_AIMING_H
#define T1_ENT_AIMING_H

#include "map_structures/base_engine/base_engine.h"

class Entity;
class BuildingsMap;
class World;

class Aiming
{
public:
	static PixelCoord aimForward(const Entity& entity, const World& world);
	static PixelCoord aimOnBuilding(const Entity& entity, const BuildingsMap& buildingsMap);
	static PixelCoord aimOnEntity(const Entity& entity, const World& world);
	static PixelCoord aimOnShell(const Entity& entity, const World& world);
};

#endif // T1_ENT_AIMING_H
