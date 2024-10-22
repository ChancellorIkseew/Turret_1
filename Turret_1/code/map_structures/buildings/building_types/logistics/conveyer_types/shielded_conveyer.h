#pragma once
#ifndef SHIELDED_CONVEYER_H
#define SHIELDED_CONVEYER_H

#include "SFML/Graphics.hpp"

#include "map_structures/buildings/building_types/logistics/conveyer.h"


class ShieldedConveyer : public Conveyer
{
public:

	ShieldedConveyer(char type, char direction, short durability, short size, const TileCoord tile, Team* team);
	~ShieldedConveyer() = default;

	void draw(sf::RenderWindow& window) override final;
	
};

#endif // SHIELDED_CONVEYER_H
