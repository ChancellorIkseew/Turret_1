#pragma once
#ifndef T1_AUXILARY_BUILDING_H
#define T1_AUXILARY_BUILDING_H

#include "map_structures/buildings/building/building.h"


class Auxilary : public Building
{
public:

	Auxilary(int type, short durability, short size, const TileCoord tile, Team* team);
	virtual ~Auxilary() = default;

	void draw(sf::RenderWindow& window) override final;

};

#endif // T1_AUXILARY_BUILDING_H
