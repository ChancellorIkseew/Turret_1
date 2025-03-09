
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initUtil(std::map<BuildingType, BuildingIco>& util)
{
	util[BuildingType::REMOVE] = BuildingIco(BuildingType::REMOVE, sf::Vector2i(10, 52));
}
