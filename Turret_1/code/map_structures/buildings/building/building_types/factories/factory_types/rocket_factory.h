#pragma once
#ifndef ROCKET_FACTORY_H
#define ROCKET_FACTORY_H

#include "map_structures/buildings/building/building_types/factories/factory.h"

#include "SFML/Graphics.hpp"


class RocketFactory final : public Factory
{
protected:

public:

	RocketFactory(int v_type, short v_durability, short v_size, int tileX, int tileY);
	RocketFactory();
	~RocketFactory() = default;

	void interact() override;
	void produceResource() override;

	bool canAccept(int resType) override;

	void animation();
	void draw(sf::RenderWindow& window) override;

};


#endif // ROCKET_FACTORY_H
