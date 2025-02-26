
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initLogistics(std::map<BuildingType, BuildingIco>& logistics)
{
	logistics[BuildingType::STANDARD_CONVEYER] = BuildingIco(BuildingType::STANDARD_CONVEYER);
	logistics[BuildingType::SHIELDED_CONVEYER] = BuildingIco(BuildingType::SHIELDED_CONVEYER);
	logistics[BuildingType::INTERSECTION] = BuildingIco(BuildingType::INTERSECTION);
	logistics[BuildingType::ROUTER] = BuildingIco(BuildingType::ROUTER);
	logistics[BuildingType::BRIDGE] = BuildingIco(BuildingType::BRIDGE);
}
