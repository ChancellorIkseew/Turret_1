#pragma once
#ifndef STONE_TOWER_H
#define STONE_TOWER_H

#include "../tower.h"

class StoneTower : public Tower
{

public:

	StoneTower(char v_type, short v_durability, short v_size, int tileX, int tileY);
	StoneTower();
	~StoneTower() = default;

	void draw(sf::RenderWindow& window) override;

};


#endif // STONE_TOWER_H
