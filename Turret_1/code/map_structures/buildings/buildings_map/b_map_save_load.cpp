

#include "buildings_map.h"

#include <iostream>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>


void BuildingsMap::save(cereal::BinaryOutputArchive& archive) const
{
	archive(mapSize);
	int num = 0;
	for (auto& line : buildingsMap)
		for (auto& building : line)
			if (building != nullptr && building->getType() != BuildingType::AUXILARY)
				++num;

	archive(num);

	for (auto& line : buildingsMap)
		for (auto& building : line)
			if (building != nullptr && building->getType() != BuildingType::AUXILARY)
				building->save(archive);
}

void BuildingsMap::load(cereal::BinaryInputArchive& archive)
{
	archive(mapSize);
	int num;
	archive(num);
	buildingsMap.resize(mapSize.x);
	buildingsMap.reserve(mapSize.x);
	for (auto& line : buildingsMap)
	{
		line.resize(mapSize.y);
		line.reserve(mapSize.y);
		for (auto& building : line)
		{
			building = nullptr;
		}
	}

	for (int i = 0; i < num; ++i)
	{
		std::shared_ptr<Building> building;
		building->load(archive);
		TileCoord tile = building->getTileCoord();
		buildingsMap[tile.x][tile.y] = std::move(building);
	}
}
