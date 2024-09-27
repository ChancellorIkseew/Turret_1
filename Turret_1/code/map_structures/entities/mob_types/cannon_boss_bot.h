#pragma once
#ifndef CANNON_BOSS_BOT_H
#define CANNON_BOSS_BOT_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/entity/entity.h"
#include "map_structures/base_engine/tile_coord.h"


class CannonBossBot : public Entity
{
public:
	CannonBossBot(int type);
	~CannonBossBot() = default;

	PixelCoord findDestinationCoord() const override final;
	void shoot() override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // CANNON_BOSS_BOT_H
