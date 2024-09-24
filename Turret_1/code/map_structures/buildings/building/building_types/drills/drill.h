#pragma once
#ifndef DRILL_H
#define DRILL_H

#include "map_structures/buildings/building/building.h"


class Drill : public Building
{
protected:

	float rotorAngle;

	int timer;

public:

	Drill(int type, short durability, short size, const TileCoord tile);
	Drill();
	virtual ~Drill() = default;

	void mineResource(int amountFromOneTile);

};


#endif // DRILL_H
