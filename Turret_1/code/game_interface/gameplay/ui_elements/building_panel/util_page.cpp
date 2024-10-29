
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initUtil(std::map<uint16_t, BuildingIco>& util)
{
	util[REMOVE] = BuildingIco(REMOVE, sf::Vector2u(10, 52));
}
