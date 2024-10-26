#pragma once
#ifndef BIG_DRILL_H
#define BIG_DRILL_H

#include <SFML/Graphics.hpp>
#include "map_structures/buildings/building_types/drills/drill.h"


class BigDrill final : public Drill
{
public:
	BigDrill(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	~BigDrill() = default;

	void interact() override final;

	void animation() override;
	void draw(sf::RenderWindow& window) override;
	
};

#endif // BIG_DRILL_H
