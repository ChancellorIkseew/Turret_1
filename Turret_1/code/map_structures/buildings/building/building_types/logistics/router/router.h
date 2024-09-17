#pragma once
#ifndef BUILDING_ROUTER_H
#define BUILDING_ROUTER_H

#include "../../../building.h"
#include "SFML/Graphics.hpp"

class Router : public Building
{
public:

	Router(int v_type, short v_durability, short v_size, int tileX, int tileY);
	Router();
	~Router();

	void interact() override;
	void placeResourceUnit(int type) override;

	bool canAccept(int resType) override;
	bool isThisPositionFree(int position) override;

	void draw(sf::RenderWindow& window) override;

};


#endif // BUILDING_ROUTER_H
