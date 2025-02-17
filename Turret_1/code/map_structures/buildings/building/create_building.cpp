
#include <iostream>

#include "buildings_enum.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "map_structures/pre-settings/pre-settings.h"

#include "map_structures/buildings/building_types/auxilary/auxilary.h"
#include "map_structures/buildings/building_types/walls/wall_types/stone_wall.h"
#include "map_structures/buildings/building_types/walls/tower_types/stone_tower.h"
//#include "map_structures/buildings/building_types/drills/drill.h"
//#include "map_structures/buildings/building_types/drills/drill_types/small_drill.h"
//#include "map_structures/buildings/building_types/drills/drill_types/big_drill.h"
//#include "map_structures/buildings/building_types/logistics/conveyer_types/standard_conveyer.h"
//#include "map_structures/buildings/building_types/logistics/conveyer_types/shielded_conveyer.h"
//#include "map_structures/buildings/building_types/logistics/bridge/bridge.h"
//#include "map_structures/buildings/building_types/logistics/router/router.h"
#include "map_structures/buildings/building_types/storages/core_types/core_mk2.h"
//#include "map_structures/buildings/building_types/factories/factory_types/shell_factory.h"
//#include "map_structures/buildings/building_types/factories/factory_types/rocket_factory.h"


std::shared_ptr<Building> Building::createBuilding(const uint16_t type, const char direction, const TileCoord tile, Team* const team)
{
	int32_t durability = 0;
	uint8_t size = 1;

	if (type != AUXILARY)
	{
		durability = t1::bc::buildingsInfoTable[type].durability * PreSettings::getBuildings().maxDurabilityModifier;
		size = t1::bc::buildingsInfoTable[type].size;
	}

	switch (type)
	{
	case AUXILARY:
		return std::make_shared<Auxilary>(AUXILARY, durability, size, tile, team);

	case CORE_MK1:
		return nullptr;
	case CORE_MK2:
		return std::make_shared<CoreMK2>(CORE_MK2, durability, size, tile, team);
	case CORE_MK3:
		return nullptr;
		
	case STONE_WALL:
		return std::make_shared<StoneWall>(STONE_WALL, durability, size, tile, team);/*
	case CONCRETE_WALL:
		break;
	case URANIUM_WALL:
		break;

	case STONE_TOWER:
		return std::make_shared<StoneTower>(STONE_TOWER, durability, size, tile, team);
	case CONCRETE_TOWER:
		break;
	case URANIUM_TOWER:
		break;

	case STANDARD_CONVEYER:
		return std::make_shared<StandardConveyer>(STANDARD_CONVEYER, direction, durability, size, tile, team);
	case SHIELDED_CONVEYER:
		return std::make_shared<ShieldedConveyer>(SHIELDED_CONVEYER, direction, durability, size, tile, team);

	case BRIDGE:
		return std::make_shared<Bridge>(BRIDGE, direction, durability, size, tile, team);
	case ROUTER:
		return std::make_shared<Router>(ROUTER, durability, size, tile, team);
	case SORTER:
		break;

	case SMALL_DRILL:
		return std::make_shared<SmallDrill>(SMALL_DRILL, durability, size, tile, team);
	case BIG_DRILL:
		return std::make_shared<BigDrill>(BIG_DRILL, durability, size, tile, team);
	case EFFECTIVE_DRILL:
		break;
	case REINFORCED_DRILL:
		break;

	case SHELL_FACTORY:
		return std::make_shared<ShellFactory>(SHELL_FACTORY, durability, size, tile, team);
	case ROCKET_FACTORY:
		return std::make_shared<RocketFactory>(ROCKET_FACTORY, durability, size, tile, team);
		*/
	default:
		std::cout << "building_type does not exist. type: " << type << '\n';
		return nullptr;
	}
}
