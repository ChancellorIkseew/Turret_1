#pragma once
#ifndef SHIELDED_CONVEYER_H
#define SHIELDED_CONVEYER_H

#include "SFML/Graphics.hpp"

#include "map_structures/buildings/building/building_types/logistics/conveer.h"


class ShieldedConveyer : public Conveyer
{
public:

	ShieldedConveyer(char type, char direction, short durability, short size, const TileCoord tile);
	~ShieldedConveyer() = default;

	void load(std::ifstream& fin) override;

	void draw(sf::RenderWindow& window) override;
	
};

#endif // SHIELDED_CONVEYER_H
