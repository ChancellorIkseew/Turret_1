#pragma once
#ifndef CONVEYER_H
#define CONVEYER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "map_structures/buildings/building/building.h"
#include "map_structures/resources/resource_unit.h"


class Conveyer : public Building
{
protected:
	int timer;
	float speed;
	std::vector<ResourceUnit> resUnits;

public:
	Conveyer(const uint16_t type, const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	virtual ~Conveyer();

	void save(std::ofstream& fout) const override final;
	virtual void load(std::ifstream& fin) override final;

	virtual void interact() override final;
	void addToInventory(ResourceUnit& unit) override final;
	bool canAccept(const ResourceUnit& unit) const override final;
	
};

#endif // CONVEYER_H
