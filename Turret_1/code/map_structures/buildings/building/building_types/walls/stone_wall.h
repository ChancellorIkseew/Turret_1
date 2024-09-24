#pragma once
#ifndef STONE_WALL_H
#define STONE_WALL_H

#include "map_structures/buildings/building/building.h"

class StoneWall : public Building
{

public:

	StoneWall(char type, short durability, short size, const TileCoord tile);
	~StoneWall() = default;

	void draw(sf::RenderWindow& window) override;

};

#endif // STONE_WALL_H
