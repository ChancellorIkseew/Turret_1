#pragma once
#ifndef DRILL_H
#define DRILL_H

#include "../../building.h"

#include "SFML/Graphics.hpp"


class Drill : public Building
{
protected:

	float rotorAngle;

	int timer;

public:

	Drill(int v_type, short v_durability, short v_size, int tileX, int tileY);
	Drill();
	virtual ~Drill() = default;

	void interact() override;
	virtual void mineResource();
	void placeResourceUnit(int type) override;

	virtual void draw(sf::RenderWindow& window) override = 0;
	
};


#endif // DRILL_H
