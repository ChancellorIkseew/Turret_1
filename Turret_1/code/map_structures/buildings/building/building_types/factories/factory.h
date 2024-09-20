#pragma once
#ifndef FACTORY_H
#define FACTORY_H

#include "map_structures/buildings/building/building.h"


class Factory : public Building
{
protected:

	int timer;

public:

	Factory(int v_type, short v_durability, short v_size, int tileX, int tileY);
	Factory() = default;
	virtual ~Factory() = default;

	virtual void produceResource() = 0;
	bool isThisPositionFree(int position) override final;

};


#endif // SHELL_FACTORY_H
