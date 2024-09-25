#pragma once
#ifndef LASER_BOT_H
#define LASER_BOT_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/entity.h"
#include "map_structures/base_engine/tile_coord.h"


class LaserBot : public Entity
{
private:

	void initCombatData() override final;

public:

	LaserBot(int type, PixelCoord coord, float curentAngleDeg, short curentDurability);
	LaserBot(int type);
	~LaserBot() = default;

	void shoot() override final;
	PixelCoord findShootingAim() const override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // LASER_BOT_H
