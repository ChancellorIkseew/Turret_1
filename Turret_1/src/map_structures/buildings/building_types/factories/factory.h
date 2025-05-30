#pragma once
#ifndef FACTORY_H
#define FACTORY_H

#include "map_structures/buildings/building/building.h"


class Factory : public Building
{
protected:
	int timer = 0;

public:
	Factory(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	Factory() = default;
	virtual ~Factory() = default;

	virtual void produceResource() = 0;

};

#endif // SHELL_FACTORY_H
