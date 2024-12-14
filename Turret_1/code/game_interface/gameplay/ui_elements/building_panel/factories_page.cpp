
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initFactories(std::map<uint16_t, BuildingIco>& factories)
{
	factories[SHELL_FACTORY] = BuildingIco(SHELL_FACTORY);
	factories[ROCKET_FACTORY] = BuildingIco(ROCKET_FACTORY);
}
