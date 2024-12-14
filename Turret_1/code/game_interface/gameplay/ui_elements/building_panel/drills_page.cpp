
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initDrills(std::map<uint16_t, BuildingIco>& drills)
{
	drills[SMALL_DRILL] = BuildingIco(SMALL_DRILL);
	drills[BIG_DRILL] = BuildingIco(BIG_DRILL);
	drills[EFFECTIVE_DRILL] = BuildingIco(EFFECTIVE_DRILL);
	drills[REINFORCED_DRILL] = BuildingIco(REINFORCED_DRILL);
}
