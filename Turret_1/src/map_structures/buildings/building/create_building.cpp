
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

using Info = BuildingsInfoTable;

std::shared_ptr<Building> Building::createBuilding(const BuildingType type, const char direction, const TileCoord tile, Team* const team)
{
	const int16_t durability = Info::at(type).durability;
	const float modifier = world->getPreSettings().getBuildings().maxDurabilityModifier;
	const int16_t durabilityModified = static_cast<int16_t>(static_cast<float>(durability) * modifier);
	const uint8_t size = Info::at(type).size;

	switch (type)
	{
	case BuildingType::AUXILARY:
		return std::make_shared<Auxilary>(tile, team);

	case BuildingType::CORE_MK1:
		return nullptr;
	case BuildingType::CORE_MK2:
		return std::make_shared<CoreMK2>(durabilityModified, size, tile, team);
	case BuildingType::CORE_MK3:
		return nullptr;
		
	case BuildingType::STONE_WALL:
		return std::make_shared<StoneWall>(durabilityModified, size, tile, team);/*
	case BuildingType::CONCRETE_WALL:
		break;
	case BuildingType::URANIUM_WALL:
		break;*/

	case BuildingType::AUTOCANNON_TURRET:
	{
		std::shared_ptr<StoneTower> tower = std::make_shared<StoneTower>(durabilityModified, size, tile, team);
		tower->setTurret(BuildingType::AUTOCANNON_TURRET);
		return tower;
	}
	case BuildingType::ROCKET_TURRET:
	{
		std::shared_ptr<StoneTower> tower = std::make_shared<StoneTower>(durabilityModified, size, tile, team);
		tower->setTurret(BuildingType::ROCKET_TURRET);
		return tower;
	}
		
	case BuildingType::STANDARD_CONVEYER:
		return std::make_shared<StandardConveyer>(direction, durabilityModified, size, tile, team);
	case BuildingType::SHIELDED_CONVEYER:
		return std::make_shared<ShieldedConveyer>(direction, durabilityModified, size, tile, team);

	case BuildingType::INTERSECTION:
		return std::make_shared<Intersection>(durabilityModified, size, tile, team);
	case BuildingType::BRIDGE:
		return std::make_shared<Bridge>(direction, durabilityModified, size, tile, team);
	case BuildingType::ROUTER:
		return std::make_shared<Router>(durabilityModified, size, tile, team);
	case BuildingType::SORTER:
		break;

	case BuildingType::SMALL_DRILL:
		return std::make_shared<SmallDrill>(durabilityModified, size, tile, team);
	case BuildingType::BIG_DRILL:
		return std::make_shared<BigDrill>(durabilityModified, size, tile, team);/*
	case BuildingType::EFFECTIVE_DRILL:
		break;
	case BuildingType::REINFORCED_DRILL:
		break;*/

	case BuildingType::SHELL_FACTORY:
		return std::make_shared<ShellFactory>(durabilityModified, size, tile, team);
	case BuildingType::ROCKET_FACTORY:
		return std::make_shared<RocketFactory>(durabilityModified, size, tile, team);
		
	default:
		std::cout << "building_type does not exist. type: " << static_cast<uint16_t>(type) << '\n';
		return nullptr;
	}
}
