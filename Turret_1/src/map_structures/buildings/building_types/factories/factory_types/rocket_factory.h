#pragma once
#ifndef ROCKET_FACTORY_H
#define ROCKET_FACTORY_H

#include <cereal/types/polymorphic.hpp>
#include "map_structures/buildings/building_types/factories/factory.h"

class RocketFactory final : public Factory
{
public:

	RocketFactory(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	RocketFactory() = default;
	~RocketFactory() = default;

	void interact() override final;
	void produceResource() override final;
	BuildingType getType() const override final { return BuildingType::ROCKET_FACTORY; }

	bool canAccept(const ResType resType) const override final;

	void animation();
	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(RocketFactory)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Building, RocketFactory)

#endif // ROCKET_FACTORY_H
