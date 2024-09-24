#pragma once
#ifndef BIG_DRILL_H
#define BIG_DRILL_H

#include "map_structures/buildings/building/building_types/drills/drill.h"

#include "SFML/Graphics.hpp"


class BigDrill final : public Drill
{
public:

	BigDrill(int type, short durability, short size, const TileCoord tile);
	BigDrill();
	~BigDrill() = default;

	void interact() override final;

	void animation() override;
	void draw(sf::RenderWindow& window) override;
	
};


#endif // BIG_DRILL_H
