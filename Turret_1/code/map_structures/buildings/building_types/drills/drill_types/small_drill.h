#pragma once
#ifndef SMALL_DRILL_H
#define SMALL_DRILL_H

#include "../drill.h"

#include "SFML/Graphics.hpp"


class SmallDrill final : public Drill
{
public:

	SmallDrill(int type, short durability, short size, const TileCoord tile);
	~SmallDrill() = default;

	void interact() override final;

	void animation() override;
	void draw(sf::RenderWindow& window) override;
	
};


#endif // SMALL_DRILL_H
