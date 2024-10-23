#pragma once
#ifndef CANNON_BOSS_BOT_H
#define CANNON_BOSS_BOT_H

#include <SFML\Graphics.hpp>
#include "map_structures/entities/entity/entity.h"


class CannonBossBot : public Entity
{
public:
	CannonBossBot(const uint16_t type, Team* const team);
	~CannonBossBot() = default;

	PixelCoord findDestinationCoord() const override final;
	void shoot() override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // CANNON_BOSS_BOT_H
