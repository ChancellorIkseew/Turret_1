#pragma once
#ifndef ROCKET_FACTORY_H
#define ROCKET_FACTORY_H

#include "map_structures/buildings/building_types/factories/factory.h"

#include "SFML/Graphics.hpp"


class RocketFactory final : public Factory
{
protected:

public:

	RocketFactory(int type, short durability, short size, const TileCoord tile, Team* team);
	~RocketFactory() = default;

	void interact() override final;
	void produceResource() override final;

	bool canAccept(const int resType) const override final;

	void animation();
	void draw(sf::RenderWindow& window) override final;

};


#endif // ROCKET_FACTORY_H
