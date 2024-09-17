#pragma once
#ifndef BUILDINGS_INFO
#define BUILDINGS_INFO

#include <SFML/Graphics.hpp>

#include "../../resources/resources.h"

struct BuildingInfo
{
	sf::String buildingTitle;

	int size;
	int durability;

	AllResources costToBuild;

	sf::String description;
};

extern BuildingInfo g_BuildingsInfoArray[500];

void initBuildingsInfo();

#endif // BUILDINGS_INFO
