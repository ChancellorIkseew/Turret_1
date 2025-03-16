#pragma once
#ifndef BLUEPRINTS_H
#define BLUEPRINTS_H

#include "map_structures/buildings/building/buildings_enum.h"

struct Blueprint
{
	BuildingType type = BuildingType::VOID_;
	char direction = 'w';

	Blueprint(const BuildingType type, const char direction) :
		type(type), direction(direction) { }
	Blueprint() = default;
	~Blueprint() = default;
};

#endif // BLUEPRINTS_H
