#pragma once
#ifndef CONVEYER_H
#define CONVEYER_H

#include <vector>
#include <cereal/archives/binary.hpp>
#include "map_structures/buildings/building/building.h"
#include "map_structures/resources/resource_unit.h"


class Conveyer : public Building
{
protected:
	int timer = 0;
	std::vector<ResourceUnit> resUnits;

public:
	Conveyer(const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	Conveyer() = default;

	void save(cereal::BinaryOutputArchive& archive) const override final;
	virtual void load(cereal::BinaryInputArchive& archive) override final;

	virtual void interact() override final;
	void addToInventory(ResourceUnit& unit) override final;
	bool canAccept(const ResourceUnit& unit) const override final;
	virtual const float getTransmitionSpeed() = 0;
	
};

#endif // CONVEYER_H
