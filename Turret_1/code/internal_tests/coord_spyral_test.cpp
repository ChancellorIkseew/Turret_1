#ifndef NDEBUG

#include "coord_spyral_test.h"

#include "map_structures/base_engine/base_engine.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/world/world.h"


void spiralTest(World& world)
{
	for (int i = 0; i < 4109; ++i)
	{
		world.getBuildingsMap().placeBuilding(BuildingType::STONE_WALL, '0', t1::be::coordSpyralArr[i] + TileCoord(50, 50), world.getTeam("player"));
	}
}


#endif // NDEBUG
