#pragma once
#ifndef STANDARD_BOT_H
#define STANDARD_BOT_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/entity/entity.h"
#include "map_structures/base_engine/tile_coord.h"


class StandardBot : public Entity
{
public:
	StandardBot(int type, Team* team);
	~StandardBot() = default;

	void shoot() override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // STANDARD_BOT_H
