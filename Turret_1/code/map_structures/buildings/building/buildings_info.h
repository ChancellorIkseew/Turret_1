#pragma once
#ifndef BUILDINGS_INFO
#define BUILDINGS_INFO

#include <map>
#include <SFML/Graphics.hpp>

#include "map_structures/resources/all_resources.h"

struct BuildingInfo
{
	sf::String buildingTitle;

	uint8_t size;
	int16_t durability;

	AllResources costToBuild;

	sf::String description;
};

namespace t1::bc
{
	extern std::map<uint16_t, const BuildingInfo> buildingsInfoTable;

	void addBuildingsInfo(uint16_t type, const BuildingInfo info);
}

#endif // BUILDINGS_INFO
