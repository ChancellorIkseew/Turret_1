#pragma once
#ifndef STANDARD_BOT_H
#define STANDARD_BOT_H

#include <SFML\Graphics.hpp>
#include "map_structures/entities/entity/entity.h"


class StandardBot : public Entity
{
public:
	StandardBot(const uint16_t type, Team* const team);
	~StandardBot() = default;

	void shoot(const BuildingsMap& buildingsMap) override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // STANDARD_BOT_H
