#pragma once
#ifndef BUILDING_ROUTER_H
#define BUILDING_ROUTER_H

#include "SFML/Graphics.hpp"
#include "map_structures/buildings/building/building.h"


class Router : public Building
{
public:

	Router(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	~Router() = default;

	void interact() override;
	bool canAccept(const uint16_t resType) const override;

	void draw(sf::RenderWindow& window) override;

};

#endif // BUILDING_ROUTER_H
