#pragma once
#ifndef SHELL_FACTORY_H
#define SHELL_FACTORY_H

#include <cereal/types/polymorphic.hpp>
#include "map_structures/buildings/building_types/factories/factory.h"

class ShellFactory final : public Factory
{
public:

	ShellFactory(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	ShellFactory() = default;
	~ShellFactory() = default;

	void interact() override final;
	void produceResource() override final;
	BuildingType getType() const override final { return BuildingType::SHELL_FACTORY; }

	bool canAccept(const ResType resType) const override final;

	void animation() override final;
	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(ShellFactory)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Building, ShellFactory)

#endif // SHELL_FACTORY_H
