#pragma once
#ifndef STONE_WALL_H
#define STONE_WALL_H

#include <cereal/types/polymorphic.hpp>
#include "map_structures/buildings/building/building.h"

class StoneWall : public Building
{
public:
	StoneWall(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	StoneWall() = default;
	~StoneWall() = default;

	BuildingType getType() const override final { return BuildingType::STONE_WALL; }

	void draw(sf::RenderWindow& window) override;

};

CEREAL_REGISTER_TYPE(StoneWall)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Building, StoneWall)

#endif // STONE_WALL_H
