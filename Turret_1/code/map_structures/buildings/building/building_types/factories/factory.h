#pragma once
#ifndef FACTORY_H
#define FACTORY_H

#include "map_structures/buildings/building/building.h"


class Factory : public Building
{
protected:

	int timer;

public:

	Factory(int type, short durability, short size, const TileCoord tile);
	Factory() = default;
	virtual ~Factory() = default;

	virtual void produceResource() = 0;
	bool isThisPositionFree(int position) const override final;

};


#endif // SHELL_FACTORY_H
