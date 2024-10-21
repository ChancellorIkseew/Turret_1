#pragma once
#ifndef SHELL_FACTORY_H
#define SHELL_FACTORY_H

#include "map_structures/buildings/building_types/factories/factory.h"

#include "SFML/Graphics.hpp"


class ShellFactory final : public Factory
{
protected:

public:

	ShellFactory(int type, short durability, short size, const TileCoord tile, Team* team);
	~ShellFactory() = default;

	void interact() override final;
	void produceResource() override final;

	bool canAccept(const uint16_t resType) const override final;

	void animation() override final;
	void draw(sf::RenderWindow& window) override final;

};


#endif // SHELL_FACTORY_H
