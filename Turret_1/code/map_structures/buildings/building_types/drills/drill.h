#pragma once
#ifndef DRILL_H
#define DRILL_H

#include "map_structures/buildings/building/building.h"


class Drill : public Building
{
protected:
	int timer = 0;
	float rotorAngle = 0.0f;

public:
	Drill(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	Drill() = default;
	virtual ~Drill() = default;

	void mineResource(const int amountFromOneTile, const int storageCapacity);

};

#endif // DRILL_H
