#pragma once
#ifndef STONE_WALL_H
#define STONE_WALL_H

#include "map_structures/buildings/building/building.h"

class StoneWall : public Building
{
public:
	StoneWall(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	~StoneWall() = default;

	BuildingType getType() const override final { return BuildingType::STONE_WALL; }

	void draw(sf::RenderWindow& window) override;

};

#endif // STONE_WALL_H
