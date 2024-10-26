
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initStorages(std::map<uint16_t, BuildingIco>& walls)
{
	walls[CORE_MK1] = BuildingIco(CORE_MK1);
	walls[CORE_MK2] = BuildingIco(CORE_MK2);
}
