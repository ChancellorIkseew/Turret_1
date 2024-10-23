#pragma once
#ifndef STANDARD_CONVEYER_H
#define STANDARD_CONVEYER_H

#include "SFML/Graphics.hpp"
#include "map_structures/buildings/building_types/logistics/conveyer.h"


class StandardConveyer : public Conveyer
{
public:
	StandardConveyer(const uint16_t type, const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	~StandardConveyer() = default;

	void draw(sf::RenderWindow& window) override final;

};

#endif // STANDARD_CONVEYER_H
