
#include "map_structures/entities/turret/turret.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/entities/turret_types/autocannon_turret.h"
#include "map_structures/entities/turret_types/rocket_turret.h"


std::unique_ptr<Turret> Turret::createTurret(const BuildingType type, const TileCoord tile, Team* const team)
{
	
	switch (type)
	{
	case BuildingType::AUTOCANNON_TURRET:
		return std::make_unique<AutocannonTurret>(tile, team);
	case BuildingType::ROCKET_TURRET:
		return std::make_unique<RocketTurret>(tile, team);
	default:
		return nullptr;
	}
	
}
