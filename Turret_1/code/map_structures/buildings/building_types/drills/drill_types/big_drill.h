#pragma once
#ifndef BIG_DRILL_H
#define BIG_DRILL_H

#include <cereal/types/polymorphic.hpp>
#include "map_structures/buildings/building_types/drills/drill.h"

class BigDrill final : public Drill
{
public:
	BigDrill(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	BigDrill() = default;
	~BigDrill() = default;

	void interact() override final;
	BuildingType getType() const override final { return BuildingType::BIG_DRILL; }

	void animation() override;
	void draw(sf::RenderWindow& window) override;
	
};

CEREAL_REGISTER_TYPE(BigDrill)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Building, BigDrill)

#endif // BIG_DRILL_H
