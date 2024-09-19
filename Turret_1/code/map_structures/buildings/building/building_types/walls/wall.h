#pragma once
#ifndef STONE_WALL_H
#define STONE_WALL_H

#include "map_structures/buildings/building/building.h"

class StoneWall : public Building
{

public:

	StoneWall(char v_type, short v_durability, short v_size, int tileX, int tileY);
	StoneWall();
	~StoneWall() = default;

	void draw(sf::RenderWindow& window) override;

};


#endif // STONE_WALL_H
