#pragma once
#ifndef STONE_TOWER_H
#define STONE_TOWER_H

#include <cereal/types/polymorphic.hpp>
#include "map_structures/buildings/building_types/walls/tower.h"

class StoneTower : public Tower
{
public:
	StoneTower(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	StoneTower() = default;
	~StoneTower() = default;

	BuildingType getType() const override final { return BuildingType::STONE_TOWER; }

	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(StoneTower)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Building, StoneTower)

#endif // STONE_TOWER_H
