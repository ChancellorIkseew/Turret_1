#pragma once
#ifndef BUILDING_INTERSECTION_H
#define BUILDING_INTERSECTION_H

#include <cereal/types/polymorphic.hpp>
#include "map_structures/buildings/building/building.h"

class Intersection : public Building
{
private:
	std::list<ResourceUnit> resUnits;
	int timer = 0;

public:
	Intersection(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	Intersection() = default;
	~Intersection() = default;

	void placeUnit();
	void interact() override;
	bool canAccept(const ResType resType) const override;
	void addToInventory(ResourceUnit& unit) override final;
	BuildingType getType() const override final { return BuildingType::ROUTER; }

	void draw(sf::RenderWindow& window) override;

};

CEREAL_REGISTER_TYPE(Intersection)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Building, Intersection)

#endif // BUILDING_ROUTER_H
