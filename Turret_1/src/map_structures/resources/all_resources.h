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
	std::map<ResType, uint32_t> allResources;

	AllResources(const uint32_t stone, const uint32_t iron, const uint32_t copper, const uint32_t silicon, const uint32_t coal, const uint32_t sulfur);
	AllResources(const std::map<ResType, uint32_t> allResources);
	AllResources() = default;
	~AllResources() = default;

	void save(cereal::BinaryOutputArchive& archive) const{
		archive(allResources);
	}
	void load(cereal::BinaryInputArchive& archive) {
		archive(allResources);
	}

	uint32_t getQuantity(const ResType type) const { return allResources.at(type); }
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
