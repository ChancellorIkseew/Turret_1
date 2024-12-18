#pragma once
#ifndef SNIPER_BOT_H
#define SNIPER_BOT_H

#include <SFML\Graphics.hpp>
#include "map_structures/entities/entity/entity.h"


class RocketBot : public Entity
{
public:
	RocketBot(const uint16_t type, Team* const team);
	~RocketBot() = default;

	void shoot(const BuildingsMap& buildingsMap) override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // SNIPER_BOT_H
