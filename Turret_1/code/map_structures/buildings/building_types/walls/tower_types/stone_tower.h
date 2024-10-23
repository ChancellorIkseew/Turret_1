#pragma once
#ifndef STONE_TOWER_H
#define STONE_TOWER_H

#include "map_structures/buildings/building_types/walls/tower.h"

class StoneTower : public Tower
{
public:
	StoneTower(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	~StoneTower() = default;

	void draw(sf::RenderWindow& window) override;

};

#endif // STONE_TOWER_H
