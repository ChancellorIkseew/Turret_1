#pragma once
#ifndef STONE_TOWER_H
#define STONE_TOWER_H

#include "map_structures/buildings/building_types/walls/tower.h"

class StoneTower : public Tower
{

public:

	StoneTower(char type, short durability, short size, const TileCoord tile, Team* team);
	~StoneTower() = default;

	void draw(sf::RenderWindow& window) override;

};

#endif // STONE_TOWER_H
