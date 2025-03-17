#pragma once
#ifndef BUILDINGS_INFO
#define BUILDINGS_INFO

#include <map>
#include <SFML/Graphics.hpp>

#include "map_structures/resources/all_resources.h"
#include "buildings_enum.h"

struct BuildingInfo
{
	sf::String buildingTitle;

	uint8_t size = 0;
	int16_t durability = 0;

	AllResources costToBuild;
	sf::IntRect icoRect;

	sf::String description;
};

class BuildingsInfoTable
{
private:
	static std::map<BuildingType, const BuildingInfo> table;

public:
	static const BuildingInfo at(const BuildingType type);
	static bool exists(const BuildingType type);
	static void addBuildingsInfo(const BuildingType type, const BuildingInfo info);
};

#endif // BUILDINGS_INFO
