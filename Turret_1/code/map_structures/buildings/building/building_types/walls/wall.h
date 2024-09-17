#pragma once
#ifndef STONE_WALL_H
#define STONE_WALL_H

#include "../../building.h"

class StoneWall : public Building
{

public:

	StoneWall(char v_type, short v_durability, short v_size, int tileX, int tileY);
	StoneWall();
	~StoneWall();

	void draw(sf::RenderWindow& window) override;

};


#endif // STONE_WALL_H
