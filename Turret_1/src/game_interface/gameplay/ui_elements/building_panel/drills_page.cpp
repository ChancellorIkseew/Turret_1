
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initDrills(std::map<BuildingType, BuildingIco>& drills)
{
	drills[BuildingType::SMALL_DRILL] = BuildingIco(BuildingType::SMALL_DRILL);
	drills[BuildingType::BIG_DRILL] = BuildingIco(BuildingType::BIG_DRILL);
	drills[BuildingType::EFFECTIVE_DRILL] = BuildingIco(BuildingType::EFFECTIVE_DRILL);
	drills[BuildingType::REINFORCED_DRILL] = BuildingIco(BuildingType::REINFORCED_DRILL);
}
