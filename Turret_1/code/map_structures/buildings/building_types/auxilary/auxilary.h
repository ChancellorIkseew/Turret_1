#pragma once
#ifndef T1_AUXILARY_BUILDING_H
#define T1_AUXILARY_BUILDING_H

#include "map_structures/buildings/building/building.h"


class Auxilary : public Building
{
public:
	Auxilary(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	virtual ~Auxilary() = default;

	void draw(sf::RenderWindow& window) override final;

};

#endif // T1_AUXILARY_BUILDING_H
