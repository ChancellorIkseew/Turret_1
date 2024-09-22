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

	Drill(int type, short durability, short size, int tileX, int tileY);
	Drill();
	virtual ~Drill() = default;

	void mineResource(int amountFromOneTile);

};


#endif // DRILL_H
