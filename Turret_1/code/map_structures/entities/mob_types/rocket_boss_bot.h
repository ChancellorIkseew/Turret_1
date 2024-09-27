#pragma once
#ifndef ROCKET_BOSS_BOT_H
#define ROCKET_BOSS_BOT_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/entity/entity.h"
#include "map_structures/base_engine/tile_coord.h"


class RocketBossBot : public Entity
{
public:
	RocketBossBot(int type);
	~RocketBossBot() = default;

	PixelCoord findDestinationCoord() const override final;
	void shoot() override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // ROCKET_BOSS_BOT_H
