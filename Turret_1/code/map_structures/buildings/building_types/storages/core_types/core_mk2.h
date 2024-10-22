#pragma once
#ifndef CORE_MK2_H
#define CORE_MK2_H

#include "SFML/Graphics.hpp"
#include "map_structures/buildings/building_types/storages/core.h"


class CoreMK2 : public Core
{
public:
	CoreMK2(int type, short durability, short size, const TileCoord tile, Team* team);
	virtual ~CoreMK2() = default;

	virtual void draw(sf::RenderWindow& window) override final;

};

#endif // CORE_MK2_H
