
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initDrills(std::map<uint16_t, BuildingIco>& walls)
{
	walls[SMALL_DRILL] = BuildingIco(SMALL_DRILL);
	walls[BIG_DRILL] = BuildingIco(BIG_DRILL);
}
