#pragma once
#ifndef BUILDINGS_INFO
#define BUILDINGS_INFO

#include <map>
#include <SFML/Graphics.hpp>

#include "map_structures/resources/resources.h"

struct BuildingInfo
{
	sf::String buildingTitle;

	int size;
	int durability;

	t1::res::AllResources costToBuild;

	sf::String description;
};

namespace t1::bc
{
	extern std::map<int, const BuildingInfo> buildingsInfoTable;

	void addBuildingsInfo(int type, const BuildingInfo info);
}

#endif // BUILDINGS_INFO
