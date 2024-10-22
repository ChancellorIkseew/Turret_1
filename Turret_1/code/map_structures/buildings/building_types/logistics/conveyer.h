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
	Conveyer(char type, char direction, short durability, short size, const TileCoord tile, Team* team);
	virtual ~Conveyer();

	void save(std::ofstream& fout) const override final;
	virtual void load(std::ifstream& fin) override final;

	virtual void interact() override final;
	void addToInventory(ResourceUnit& unit) override final;
	bool canAccept(const ResourceUnit& unit) const override final;
	
};

#endif // CONVEYER_H
