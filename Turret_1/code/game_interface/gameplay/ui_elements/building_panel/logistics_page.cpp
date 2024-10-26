
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initLogistics(std::map<uint16_t, BuildingIco>& logistics)
{
	logistics[STANDARD_CONVEYER] = BuildingIco(STANDARD_CONVEYER);
	logistics[SHIELDED_CONVEYER] = BuildingIco(SHIELDED_CONVEYER);
	logistics[ROUTER] = BuildingIco(ROUTER);
	logistics[BRIDGE] = BuildingIco(BRIDGE);
}
