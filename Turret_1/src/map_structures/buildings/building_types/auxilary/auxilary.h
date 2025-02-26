#pragma once
#ifndef T1_AUXILARY_BUILDING_H
#define T1_AUXILARY_BUILDING_H

#include "map_structures/buildings/building/building.h"


class Auxilary : public Building
{
public:
	Auxilary(const TileCoord tile, Team* const team);
	virtual ~Auxilary() = default;

	BuildingType getType() const override final { return BuildingType::AUXILARY; }

	void draw(sf::RenderWindow& window) override final;

};

#endif // T1_AUXILARY_BUILDING_H
