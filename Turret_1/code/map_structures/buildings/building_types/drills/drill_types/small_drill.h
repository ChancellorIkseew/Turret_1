#pragma once
#ifndef SMALL_DRILL_H
#define SMALL_DRILL_H

#include <SFML/Graphics.hpp>
#include "map_structures/buildings/building_types/drills/drill.h"


class SmallDrill final : public Drill
{
public:

	SmallDrill(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	~SmallDrill() = default;

	void interact() override final;

	void animation() override;
	void draw(sf::RenderWindow& window) override;
	
};

#endif // SMALL_DRILL_H
