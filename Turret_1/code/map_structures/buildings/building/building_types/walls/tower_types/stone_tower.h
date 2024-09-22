#pragma once
#ifndef STONE_TOWER_H
#define STONE_TOWER_H

#include "map_structures/buildings/building/building_types/walls/tower.h"

class StoneTower : public Tower
{

public:

	StoneTower(char type, short durability, short size, int tileX, int tileY);
	StoneTower();
	~StoneTower() = default;

	void draw(sf::RenderWindow& window) override;

};


#endif // STONE_TOWER_H
