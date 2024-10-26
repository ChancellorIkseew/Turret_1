
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initFactories(std::map<uint16_t, BuildingIco>& walls)
{
	walls[SHELL_FACTORY] = BuildingIco(SHELL_FACTORY);
	walls[ROCKET_FACTORY] = BuildingIco(ROCKET_FACTORY);
}
