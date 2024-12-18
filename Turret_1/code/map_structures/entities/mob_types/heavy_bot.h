#pragma once
#ifndef HEAVY_BOT_H
#define HEAVY_BOT_H

#include <SFML\Graphics.hpp>
#include "map_structures/entities/entity/entity.h"


class HeavyBot : public Entity
{
public:
	HeavyBot(const uint16_t type, Team* const team);
	~HeavyBot() = default;

	void shoot(const BuildingsMap& buildingsMap) override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // HEAVY_BOT_H
