#pragma once
#ifndef BLUEPRINTS_H
#define BLUEPRINTS_H

#include "map_structures/buildings/building/buildings_enum.h"
#include <cereal/archives/binary.hpp>

struct Blueprint
{
	BuildingType type = BuildingType::VOID_;
	char direction = 'w';

	Blueprint(const BuildingType type, const char direction) :
		type(type), direction(direction) { }
	Blueprint() = default;
	~Blueprint() = default;

	void save(cereal::BinaryOutputArchive& archive) const { archive(type, direction); }
	void load(cereal::BinaryInputArchive& archive) { archive(type, direction); }
};

#endif // BLUEPRINTS_H
