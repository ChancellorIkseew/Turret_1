
#include "map_structures/entities/turret/turret.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/entities/turret_types/autocannon_turret.h"
#include "map_structures/entities/turret_types/rocket_turret.h"


std::unique_ptr<Turret> Turret::createTurret(const int type, const TileCoord tile, Team* team)
{
	switch (type)
	{
	case AUTOCANNON_TURRET:
		return std::make_unique<AutocannonTurret>(AUTOCANNON_TURRET, tile, team);
	case ROCKET_TURRET:
		return std::make_unique<RocketTurret>(ROCKET_TURRET, tile, team);
	default:
		return nullptr;
	}
}
