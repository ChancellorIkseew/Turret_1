#pragma once
#ifndef LASER_BOT_H
#define LASER_BOT_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/entity/entity.h"
#include "map_structures/base_engine/tile_coord.h"


class LaserBot : public Entity
{
public:
	LaserBot(int type, Team* team);
	~LaserBot() = default;

	void shoot() override final;
	PixelCoord findShootingAim() const override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // LASER_BOT_H
