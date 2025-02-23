
#include "buildings_map.h"

#include <iostream>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>


void BuildingsMap::save(cereal::BinaryOutputArchive& archive) const
{
	std::vector<std::shared_ptr<Building>> buildings;
	for (auto& line : buildingsMap)
		for (auto& building : line)
			if (building != nullptr && building->getType() != BuildingType::AUXILARY)
				buildings.emplace_back(building);
	archive(mapSize, buildings);
}

void BuildingsMap::load(cereal::BinaryInputArchive& archive)
{
	std::vector<std::shared_ptr<Building>> buildings;
	archive(mapSize, buildings);

	buildingsMap.resize(mapSize.x);
	for (auto& line : buildingsMap)
		line.resize(mapSize.y);

	for (auto& building : buildings)
	{
		const TileCoord tile = building->getTileCoord();
		buildingsMap[tile.x][tile.y] = building;
		createAuxilary(building->getSize(), tile, building->getTeam());
	}

}
