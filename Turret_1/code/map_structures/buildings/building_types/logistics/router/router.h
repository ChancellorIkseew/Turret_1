#pragma once
#ifndef BUILDING_ROUTER_H
#define BUILDING_ROUTER_H

#include <cereal/types/polymorphic.hpp>
#include "map_structures/buildings/building/building.h"

class Router : public Building
{
public:
	Router(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	Router() = default;
	~Router() = default;

	void interact() override;
	bool canAccept(const ResType resType) const override;
	BuildingType getType() const override final { return BuildingType::ROUTER; }

	void draw(sf::RenderWindow& window) override;

};

CEREAL_REGISTER_TYPE(Router)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Building, Router)

#endif // BUILDING_ROUTER_H
