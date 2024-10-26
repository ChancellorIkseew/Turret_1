#pragma once
#ifndef DRILL_H
#define DRILL_H

#include "map_structures/buildings/building/building.h"


class Drill : public Building
{
protected:
	int timer;
	int storageCapacity;
	float rotorAngle;

public:
	Drill(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	virtual ~Drill() = default;

	void mineResource(int amountFromOneTile);

};

#endif // DRILL_H
