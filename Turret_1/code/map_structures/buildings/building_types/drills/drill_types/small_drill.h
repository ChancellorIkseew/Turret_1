#pragma once
#ifndef SMALL_DRILL_H
#define SMALL_DRILL_H

#include <cereal/types/polymorphic.hpp>
#include "map_structures/buildings/building_types/drills/drill.h"

class SmallDrill final : public Drill
{
public:
	SmallDrill(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	SmallDrill() = default;
	~SmallDrill() = default;

	void interact() override final;
	BuildingType getType() const override final { return BuildingType::SMALL_DRILL; }

	void animation() override;
	void draw(sf::RenderWindow& window) override;
	
};

CEREAL_REGISTER_TYPE(SmallDrill)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Building, SmallDrill)

#endif // SMALL_DRILL_H
