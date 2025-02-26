#pragma once
#ifndef DAMAGE_H
#define DAMAGE_H

#include "map_structures/base_engine/base_engine.h"

class World;

class Damage
{
public:
	static void createExplosion(const PixelCoord centrePixel, const int tileRadius, const float damage, const float dampingCoef, World& world);

};

#endif // DAMAGE_H
