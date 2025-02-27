
#include <iostream>

#include "buildings_enum.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/world/world.h"

#include "map_structures/buildings/building_types/auxilary/auxilary.h"
#include "map_structures/buildings/building_types/walls/wall_types/stone_wall.h"
#include "map_structures/buildings/building_types/walls/tower_types/stone_tower.h"
#include "map_structures/buildings/building_types/drills/drill_types/small_drill.h"
#include "map_structures/buildings/building_types/drills/drill_types/big_drill.h"
#include "map_structures/buildings/building_types/logistics/conveyer_types/standard_conveyer.h"
#include "map_structures/buildings/building_types/logistics/conveyer_types/shielded_conveyer.h"
#include "map_structures/buildings/building_types/logistics/bridge/bridge.h"
#include "map_structures/buildings/building_types/logistics/router/router.h"
#include "map_structures/buildings/building_types/logistics/intersection/intersection.h"
#include "map_structures/buildings/building_types/storages/core_types/core_mk2.h"
#include "map_structures/buildings/building_types/factories/factory_types/shell_factory.h"
#include "map_structures/buildings/building_types/factories/factory_types/rocket_factory.h"


std::shared_ptr<Building> Building::createBuilding(const BuildingType type, const char direction, const TileCoord tile, Team* const team)
{
	int32_t durability = t1::bc::buildingsInfoTable[type].durability * world->getPreSettings().getBuildings().maxDurabilityModifier;
	uint8_t size = t1::bc::buildingsInfoTable[type].size;

	switch (type)
	{
	case BuildingType::AUXILARY:
		return std::make_shared<Auxilary>(tile, team);

	case BuildingType::CORE_MK1:
		return nullptr;
	case BuildingType::CORE_MK2:
		return std::make_shared<CoreMK2>(durability, size, tile, team);
	case BuildingType::CORE_MK3:
		return nullptr;
		
	case BuildingType::STONE_WALL:
		return std::make_shared<StoneWall>(durability, size, tile, team);/*
	case BuildingType::CONCRETE_WALL:
		break;
	case BuildingType::URANIUM_WALL:
		break;*/

	case BuildingType::STONE_TOWER:
		return std::make_shared<StoneTower>(durability, size, tile, team);/*
	case BuildingType::CONCRETE_TOWER:
		break;
	case BuildingType::URANIUM_TOWER:
		break;*/

	case BuildingType::STANDARD_CONVEYER:
		return std::make_shared<StandardConveyer>(direction, durability, size, tile, team);
	case BuildingType::SHIELDED_CONVEYER:
		return std::make_shared<ShieldedConveyer>(direction, durability, size, tile, team);

	case BuildingType::INTERSECTION:
		return std::make_shared<Intersection>(durability, size, tile, team);
	case BuildingType::BRIDGE:
		return std::make_shared<Bridge>(direction, durability, size, tile, team);
	case BuildingType::ROUTER:
		return std::make_shared<Router>(durability, size, tile, team);
	case BuildingType::SORTER:
		break;

	case BuildingType::SMALL_DRILL:
		return std::make_shared<SmallDrill>(durability, size, tile, team);
	case BuildingType::BIG_DRILL:
		return std::make_shared<BigDrill>(durability, size, tile, team);/*
	case BuildingType::EFFECTIVE_DRILL:
		break;
	case BuildingType::REINFORCED_DRILL:
		break;*/

	case BuildingType::SHELL_FACTORY:
		return std::make_shared<ShellFactory>(durability, size, tile, team);
	case BuildingType::ROCKET_FACTORY:
		return std::make_shared<RocketFactory>(durability, size, tile, team);
		
	default:
		std::cout << "building_type does not exist. type: " << static_cast<uint16_t>(type) << '\n';
		return nullptr;
	}
}
