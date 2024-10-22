#pragma once
#ifndef STANDARD_CONVEYER_H
#define STANDARD_CONVEYER_H

#include "SFML/Graphics.hpp"

#include "map_structures/buildings/building_types/logistics/conveyer.h"


class StandardConveyer : public Conveyer
{
public:

	StandardConveyer(char type, char direction, short durability, short size, const TileCoord tile, Team* team);
	~StandardConveyer() = default;

	void draw(sf::RenderWindow& window) override final;

};

#endif // STANDARD_CONVEYER_H
