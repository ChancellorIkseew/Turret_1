#pragma once
#ifndef CORE_MK2_H
#define CORE_MK2_H

#include "SFML/Graphics.hpp"
#include "map_structures/buildings/building_types/storages/core.h"


class CoreMK2 : public Core
{
public:
	CoreMK2(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	virtual ~CoreMK2() = default;

	BuildingType getType() const override final { return BuildingType::CORE_MK2; }

	virtual void draw(sf::RenderWindow& window) override final;

};

#endif // CORE_MK2_H
