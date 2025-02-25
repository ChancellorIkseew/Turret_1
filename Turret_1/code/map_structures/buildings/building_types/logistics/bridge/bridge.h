#pragma once
#ifndef BRIDGE_H
#define BRIDGE_H

#include <cereal/types/polymorphic.hpp>
#include "map_structures/buildings/building/building.h"

class Bridge : public Building
{
public:
	Bridge(const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	Bridge() = default;
	~Bridge() = default;

	void save(cereal::BinaryOutputArchive& archive) const override final;
	void load(cereal::BinaryInputArchive& archive) override final;

	void interact() override final;
	void transmitResourceUnit();
	bool canAccept(const uint16_t resType) const override final;
	BuildingType getType() const override final { return BuildingType::BRIDGE; }

	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(Bridge)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Building, Bridge)

#endif // BRIDGE_H
