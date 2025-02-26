
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initFactories(std::map<BuildingType, BuildingIco>& factories)
{
	factories[BuildingType::SHELL_FACTORY] = BuildingIco(BuildingType::SHELL_FACTORY);
	factories[BuildingType::ROCKET_FACTORY] = BuildingIco(BuildingType::ROCKET_FACTORY);
}
