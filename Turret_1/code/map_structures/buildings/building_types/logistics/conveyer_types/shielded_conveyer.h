#pragma once
#ifndef SHIELDED_CONVEYER_H
#define SHIELDED_CONVEYER_H

#include <cereal/types/polymorphic.hpp>
#include "map_structures/buildings/building_types/logistics/conveyer.h"

class ShieldedConveyer : public Conveyer
{
public:
	ShieldedConveyer(const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	ShieldedConveyer() = default;
	~ShieldedConveyer() = default;

	BuildingType getType() const override final { return BuildingType::SHIELDED_CONVEYER; }

	void draw(sf::RenderWindow& window) override final;
	
};

CEREAL_REGISTER_TYPE(ShieldedConveyer)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Building, ShieldedConveyer)

#endif // SHIELDED_CONVEYER_H
