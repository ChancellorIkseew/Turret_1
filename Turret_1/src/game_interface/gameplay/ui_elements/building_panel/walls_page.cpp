
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initWalls(std::map<BuildingType, BuildingIco>& walls)
{
	walls[BuildingType::STONE_WALL] = BuildingIco(BuildingType::STONE_WALL);
	walls[BuildingType::STONE_BIG_WALL] = BuildingIco(BuildingType::STONE_BIG_WALL);
	walls[BuildingType::STEEL_WALL] = BuildingIco(BuildingType::STEEL_WALL);
	walls[BuildingType::STEEL_BIG_WALL] = BuildingIco(BuildingType::STEEL_BIG_WALL);
	walls[BuildingType::CONCRETE_WALL] = BuildingIco(BuildingType::STEEL_WALL);
	walls[BuildingType::CONCRETE_BIG_WALL] = BuildingIco(BuildingType::STEEL_BIG_WALL);
	walls[BuildingType::URANIUM_WALL] = BuildingIco(BuildingType::STEEL_WALL);
	walls[BuildingType::URANIUM_BIG_WALL] = BuildingIco(BuildingType::STEEL_BIG_WALL);
}
