
#include "buildings_enum.h"

#include "building_types/auxilary/auxilary.h"
#include "building_types/walls/stone_wall.h"
#include "building_types/walls/tower_types/stone_tower.h"
#include "building_types/drills/drill.h"
#include "building_types/drills/drill_types/small_drill.h"
#include "building_types/drills/drill_types/big_drill.h"
#include "building_types/logistics/conveer.h"
#include "building_types/logistics/conveer_types/shielded_conveer.h"
#include "building_types/logistics/bridge/bridge.h"
#include "building_types/logistics/router/router.h"
#include "building_types/storages/core.h"
#include "building_types/factories/factory_types/shell_factory.h"
#include "building_types/factories/factory_types/rocket_factory.h"


std::shared_ptr<Building> Building::createBuilding(int type, char direction, short durability, short size, const TileCoord tile)
{
	switch (type)
	{
	case AUXILARY:
		return std::make_shared<Auxilary>(AUXILARY, durability, size, tile);

	case CORE_MK1:
		return std::make_shared<Core>(CORE_MK1, durability, size, tile);

	case STONE_WALL:
		return std::make_shared<StoneWall>(STONE_WALL, durability, size, tile);

	case STONE_TOWER:
		return std::make_shared<StoneTower>(STONE_TOWER, durability, size, tile);

	case STANDARD_CONVEYER:
		return std::make_shared<Conveyer>(STANDARD_CONVEYER, direction, durability, size, tile);
	case SHIELDED_CONVEYER:
		return std::make_shared<ShieldedConveyer>(SHIELDED_CONVEYER, direction, durability, size, tile);

	case BRIDGE:
		return std::make_shared<Bridge>(BRIDGE, direction, durability, size, tile);
	case ROUTER:
		return std::make_shared<Router>(ROUTER, durability, size, tile);

	case SMALL_DRILL:
		return std::make_shared<SmallDrill>(SMALL_DRILL, durability, size, tile);
	case BIG_DRILL:
		return std::make_shared<BigDrill>(BIG_DRILL, durability, size, tile);
	case EFFECTIVE_DRILL:
		break;
	case REINFORCED_DRILL:
		break;

	case SHELL_FACTORY:
		return std::make_shared<ShellFactory>(SHELL_FACTORY, durability, size, tile);
	case ROCKET_FACTORY:
		return std::make_shared<RocketFactory>(ROCKET_FACTORY, durability, size, tile);

	default:
		return nullptr;
	}
}
