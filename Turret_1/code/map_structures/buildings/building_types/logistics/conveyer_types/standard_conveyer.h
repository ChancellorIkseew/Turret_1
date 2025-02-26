#pragma once
#ifndef STANDARD_CONVEYER_H
#define STANDARD_CONVEYER_H

#include <cereal/types/polymorphic.hpp>
#include "map_structures/buildings/building_types/logistics/conveyer.h"

class StandardConveyer : public Conveyer
{
public:
	StandardConveyer(const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	StandardConveyer() = default;
	~StandardConveyer() = default;

	BuildingType getType() const override final { return BuildingType::STANDARD_CONVEYER; }
	const float getTransmitionSpeed() override final { return 2.0f; }

	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(StandardConveyer)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Building, StandardConveyer)

#endif // STANDARD_CONVEYER_H
