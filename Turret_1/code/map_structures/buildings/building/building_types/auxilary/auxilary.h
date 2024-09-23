#pragma once
#ifndef T1_AUXILARY_BUILDING_H
#define T1_AUXILARY_BUILDING_H

#include "map_structures/buildings/building/building.h"


class Auxilary : public Building
{
public:

	Auxilary(int type, short durability, short size, int tileX, int tileY);
	Auxilary() = default;
	virtual ~Auxilary() = default;

};

#endif // T1_AUXILARY_BUILDING_H
