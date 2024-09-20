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

	Drill(int v_type, short v_durability, short v_size, int tileX, int tileY);
	Drill();
	virtual ~Drill() = default;

	void mineResource(int amountFromOneTile);

};


#endif // DRILL_H
