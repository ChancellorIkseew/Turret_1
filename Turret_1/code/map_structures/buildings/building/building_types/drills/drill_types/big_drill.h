#pragma once
#ifndef BIG_DRILL_H
#define BIG_DRILL_H

#include "map_structures/buildings/building/building_types/drills/drill.h"

#include "SFML/Graphics.hpp"


class BigDrill final : public Drill
{
public:

	BigDrill(int v_type, short v_durability, short v_size, int tileX, int tileY);
	BigDrill();
	~BigDrill() = default;

	void interact() override final;

	void animation() override;
	void draw(sf::RenderWindow& window) override;
	
};


#endif // BIG_DRILL_H
