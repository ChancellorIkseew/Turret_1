#pragma once
#ifndef SHELL_FACTORY_H
#define SHELL_FACTORY_H

#include "map_structures/buildings/building_types/factories/factory.h"

#include "SFML/Graphics.hpp"


class ShellFactory final : public Factory
{
protected:

public:

	ShellFactory(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	~ShellFactory() = default;

	void interact() override final;
	void produceResource() override final;

	bool canAccept(const uint16_t resType) const override final;

	void animation() override final;
	void draw(sf::RenderWindow& window) override final;

};


#endif // SHELL_FACTORY_H
