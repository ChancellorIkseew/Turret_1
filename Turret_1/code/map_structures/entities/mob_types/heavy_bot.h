#pragma once
#ifndef HEAVY_BOT_H
#define HEAVY_BOT_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/entity.h"
#include "map_structures/base_engine/tile_coord.h"


class HeavyBot : public Entity
{
private:

	void initCombatData() override final;

public:

	HeavyBot(int type, PixelCoord coord, float curentAngleDeg, short curentDurability);
	HeavyBot(int type);
	~HeavyBot() = default;

	void shoot() override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // HEAVY_BOT_H
