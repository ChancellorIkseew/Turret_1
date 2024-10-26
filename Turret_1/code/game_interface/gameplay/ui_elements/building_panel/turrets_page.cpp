
#include "buildings_pages.h"
#include "map_structures/buildings/building/buildings_enum.h"

void t1::bc::initTurrets(std::map<uint16_t, BuildingIco>& turrets)
{
	turrets[AUTOCANNON_TURRET] = BuildingIco(AUTOCANNON_TURRET);
	turrets[ROCKET_TURRET] = BuildingIco(ROCKET_TURRET);
}
