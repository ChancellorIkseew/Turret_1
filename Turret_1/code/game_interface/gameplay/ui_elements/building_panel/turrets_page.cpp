
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initTurrets(std::map<BuildingType, BuildingIco>& turrets)
{
	turrets[BuildingType::AUTOCANNON_TURRET] = BuildingIco(BuildingType::AUTOCANNON_TURRET);
	turrets[BuildingType::HEAVY_CANNON_TURRET] = BuildingIco(BuildingType::HEAVY_CANNON_TURRET);
	turrets[BuildingType::ROCKET_TURRET] = BuildingIco(BuildingType::ROCKET_TURRET);
	turrets[BuildingType::LASER_TURRET] = BuildingIco(BuildingType::LASER_TURRET);
}
