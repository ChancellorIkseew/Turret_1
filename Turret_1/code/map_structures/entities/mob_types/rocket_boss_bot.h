#pragma once
#ifndef ROCKET_BOSS_BOT_H
#define ROCKET_BOSS_BOT_H

#include <SFML\Graphics.hpp>
#include "map_structures/entities/entity/entity.h"


class RocketBossBot : public Entity
{
public:
	RocketBossBot(const uint16_t type, Team* const team);
	~RocketBossBot() = default;

	void shoot() override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // ROCKET_BOSS_BOT_H
