#pragma once
#ifndef SNIPER_BOT_H
#define SNIPER_BOT_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/entity/entity.h"
#include "map_structures/base_engine/tile_coord.h"


class RocketBot : public Entity
{
public:
	RocketBot(int type);
	~RocketBot() = default;

	PixelCoord findDestinationCoord() const override final;
	void shoot() override final;
	PixelCoord findShootingAim() const override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // SNIPER_BOT_H
