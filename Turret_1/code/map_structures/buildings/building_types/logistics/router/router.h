#pragma once
#ifndef BUILDING_ROUTER_H
#define BUILDING_ROUTER_H

#include "map_structures/buildings/building/building.h"
#include "SFML/Graphics.hpp"


class Router : public Building
{
public:

	Router(int type, short durability, short size, const TileCoord tile);
	~Router() = default;

	void interact() override;

	bool canAccept(int resType) const override;
	bool isThisPositionFree(int position) const override;

	void draw(sf::RenderWindow& window) override;

};

#endif // BUILDING_ROUTER_H
