#pragma once
#ifndef SMALL_DRILL_H
#define SMALL_DRILL_H

#include "../drill.h"

#include "SFML/Graphics.hpp"


class SmallDrill final : public Drill
{
public:

	SmallDrill(int v_type, short v_durability, short v_size, int tileX, int tileY);
	SmallDrill();
	~SmallDrill() = default;

	void interact() override final;

	void animation() override;
	void draw(sf::RenderWindow& window) override;
	
};


#endif // SMALL_DRILL_H
