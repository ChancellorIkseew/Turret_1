
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


Building* Building::createBuilding(int type, char direction, short durability, short size, const TileCoord tile)
{
	switch (type)
	{
	case AUXILARY:
		return new Auxilary(AUXILARY, durability, size, tile);

	case CORE_MK1:
		return new Core(CORE_MK1, durability, size, tile);

	case STONE_WALL:
		return new StoneWall(STONE_WALL, durability, size, tile);

	case STONE_TOWER:
		return new StoneTower(STONE_TOWER, durability, size, tile);

	case STANDARD_CONVEYER_UP:
		return new Conveyer(STANDARD_CONVEYER_UP, 'w', durability, size, tile);
	case STANDARD_CONVEYER_LEFT:
		return  new Conveyer(STANDARD_CONVEYER_LEFT, 'a', durability, size, tile);
	case STANDARD_CONVEYER_DOWN:
		return new Conveyer(STANDARD_CONVEYER_DOWN, 's', durability, size, tile);
	case STANDARD_CONVEYER_RIGHT:
		return new Conveyer(STANDARD_CONVEYER_RIGHT, 'd', durability, size, tile);

	case SHIELDED_CONVEYER_UP:
		return new ShieldedConveyer(SHIELDED_CONVEYER_UP, 'w', durability, size, tile);
	case SHIELDED_CONVEYER_LEFT:
		return  new ShieldedConveyer(SHIELDED_CONVEYER_LEFT, 'a', durability, size, tile);
	case SHIELDED_CONVEYER_DOWN:
		return new ShieldedConveyer(SHIELDED_CONVEYER_DOWN, 's', durability, size, tile);
	case SHIELDED_CONVEYER_RIGHT:
		return new ShieldedConveyer(SHIELDED_CONVEYER_RIGHT, 'd', durability, size, tile);

	case BRIDGE:
		return new Bridge(BRIDGE, direction, durability, size, tile);

	case ROUTER:
		return new Router(ROUTER, durability, size, tile);

	case SMALL_DRILL:
		return new SmallDrill(SMALL_DRILL, durability, size, tile);

	case BIG_DRILL:
		return new BigDrill(BIG_DRILL, durability, size, tile);

	case EFFECTIVE_DRILL:
		break;

	case REINFORCED_DRILL:
		break;

	case SHELL_FACTORY:
		return new ShellFactory(SHELL_FACTORY, durability, size, tile);

	case ROCKET_FACTORY:
		return new RocketFactory(ROCKET_FACTORY, durability, size, tile);

	default:
		return nullptr;
	}
}
