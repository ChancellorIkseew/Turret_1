
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initStorages(std::map<BuildingType, BuildingIco>& storages)
{
	storages[BuildingType::CORE_MK1] = BuildingIco(BuildingType::CORE_MK1);
	storages[BuildingType::CORE_MK2] = BuildingIco(BuildingType::CORE_MK2);
}
