#pragma once
#ifndef LASER_BOT_H
#define LASER_BOT_H

#include <SFML\Graphics.hpp>
#include "map_structures/entities/entity/entity.h"


class LaserBot : public Entity
{
public:
	LaserBot(const uint16_t type, Team* const team);
	~LaserBot() = default;

	void shoot() override final;
	PixelCoord findShootingAim() const override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // LASER_BOT_H
