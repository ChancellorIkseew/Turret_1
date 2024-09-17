#pragma once
#ifndef BIG_DRILL_H
#define BIG_DRILL_H

#include "../drill.h"

#include "SFML/Graphics.hpp"


class BigDrill : public Drill
{
public:

	BigDrill(int v_type, short v_durability, short v_size, int tileX, int tileY);
	BigDrill();
	~BigDrill();

	void mineResource() override;

	void animation() override;
	void draw(sf::RenderWindow& window) override;
	
};



#endif // BIG_DRILL_H