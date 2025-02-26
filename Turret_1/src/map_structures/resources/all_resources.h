#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H

#include <map>
#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>
#include "map_structures/resources/res_enum.h"

class AllResources
{
public:
	std::map<ResType, int> allResources;

	AllResources(const int stone, const int iron, const int copper, const int silicon, const int coal, const int sulfur);
	AllResources(const std::map<ResType, int> allResources);
	AllResources() = default;
	~AllResources() = default;

	void save(cereal::BinaryOutputArchive& archive) const{
		archive(allResources);
	}
	void load(cereal::BinaryInputArchive& archive) {
		archive(allResources);
	}

	int getQuantity(const ResType type) const { return allResources.at(type); }
	/*
	AllResources operator+(const AllResources& rhs)
	{
		return;
	}

	AllResources operator-(const AllResources& rhs)
	{
		return;
	}
	*/
};

#endif // RESOURCES_H
