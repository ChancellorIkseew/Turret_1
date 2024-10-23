#pragma once
#ifndef SHIELDED_CONVEYER_H
#define SHIELDED_CONVEYER_H

#include "SFML/Graphics.hpp"
#include "map_structures/buildings/building_types/logistics/conveyer.h"


class ShieldedConveyer : public Conveyer
{
public:
	ShieldedConveyer(const uint16_t type, const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	~ShieldedConveyer() = default;

	void draw(sf::RenderWindow& window) override final;
	
};

#endif // SHIELDED_CONVEYER_H
