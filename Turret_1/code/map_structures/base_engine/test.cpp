#ifndef TURRET_1_NO_TEST_BUILD

#include "test.h"

#include "tile_coord.h"
#include "map_structures/buildings/buildings_map.h"


void spiralTest()
{
	for (int i = 0; i < 4109; ++i)
	{
		BuildingsMap::constructBuilding(8, '0', { coordSpyralArr[i].x + 50, coordSpyralArr[i].y + 50 });
	}
}


#endif // TURRET_1_NO_TEST_BUILD
