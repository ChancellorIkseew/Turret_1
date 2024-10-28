
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initWalls(std::map<uint16_t, BuildingIco>& walls)
{
	walls[STONE_WALL] = BuildingIco(STONE_WALL);
	walls[STONE_TOWER] = BuildingIco(STONE_TOWER);
	walls[STEEL_WALL] = BuildingIco(STEEL_WALL);
	walls[STEEL_TOWER] = BuildingIco(STEEL_TOWER);
	walls[CONCRETE_WALL] = BuildingIco(STEEL_WALL);
	walls[CONCRETE_TOWER] = BuildingIco(STEEL_TOWER);
	walls[URANIUM_WALL] = BuildingIco(STEEL_WALL);
	walls[URANIUM_TOWER] = BuildingIco(STEEL_TOWER);
}
