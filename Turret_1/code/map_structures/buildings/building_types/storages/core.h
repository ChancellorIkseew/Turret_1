#pragma once
#ifndef CORE_H
#define CORE_H

#include "SFML/Graphics.hpp"
#include "map_structures/buildings/building/building.h"


class Core : public Building
{
public:
	Core(int type, short durability, short size, const TileCoord tile, Team* team);
	virtual ~Core() = default;

	void interact() override final;
	bool canAccept(const uint16_t resType) const override final;
	
};

#endif // CORE_H
