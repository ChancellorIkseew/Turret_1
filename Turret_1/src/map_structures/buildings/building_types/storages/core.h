#pragma once
#ifndef CORE_H
#define CORE_H

#include "SFML/Graphics.hpp"
#include "map_structures/buildings/building/building.h"

class Core : public Building
{
public:
	Core(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	Core() = default;
	virtual ~Core() = default;

	void interact() override final;
	bool canAccept(const ResType resType) const override final;
	
};

#endif // CORE_H
