
#include "path_finding.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/building.h"
#include "map_structures/entities/entity/entity.h"
#include "map_structures/team/team.h"

using namespace t1::be;
constexpr int MAX_EXPECTED_DISTANCE = 64000;

static inline TileCoord findBuildingCenter(const Building& building)
{
	int lineSize = static_cast<int>(sqrt(building.getSize()));
	TileCoord correction(lineSize / 2, lineSize / 2);
	return building.getTileCoord() + correction;
}


TileCoord t1::ent::findDestination(const Entity& entity, const BuildingsMap& buildingsMap)
{
	TileCoord core = findClosestCore(entity, buildingsMap);
	int currentDistance = pow2i(entity.currentTile.x - core.x) + pow2i(entity.currentTile.y - core.y); // SQR(real_distance)
	int newDistance = 0;

	for (int i = 1; i < 9; i += 2)
	{
		TileCoord cheekTile = entity.currentTile + coordSpyralArr[i];
		if (!buildingsMap.isVoidBuilding(cheekTile))
			continue;

		newDistance = pow2i(cheekTile.x - core.x) + pow2i(cheekTile.y - core.y); // SQR(real_distance)
		if (newDistance < currentDistance)
			return cheekTile;
	}
	return core;
}


TileCoord t1::ent::findClosestCore(const Entity& entity, const BuildingsMap& buildingsMap)
{
	const std::vector<std::shared_ptr<Building>>& cores = buildingsMap.getCores();
	if (cores.size() == 0)
		return { 0, 0 }; // возможны изменения

	int distance = 0;
	int minDistance = MAX_EXPECTED_DISTANCE;
	int index = 0;
	TileCoord entityTile = entity.getTile();
	TileCoord coreCenter(0, 0);
	for (int i = 0; i < cores.size(); ++i)
	{
		coreCenter = findBuildingCenter(*cores[i]);
		distance = pow2i(entityTile.x - coreCenter.x) + pow2i(entityTile.y - coreCenter.y); // SQR(real_distance)
		if (distance < minDistance)
		{
			minDistance = distance;
			index = i;
		}
	}

	return findBuildingCenter(*cores[index]);
}

// With comparing distances we dont use SQRT,
// because we dont need to know real distance value.
// Just find the smallest distance.


/*
	Exmple of finding building_centre

	-----------------
	|	|	|	|	|
	-----------------
	|	|	|	|	|
	-----------------
	|	|	| X	|	|
	-----------------
	|	|	|	|	|
	-----------------

	-------------
	|	|	|	|
	-------------
	|	| X	|	|
	-------------
	|	|	|	|
	-------------

	---------
	|	|	|
	---------
	|	| X	|
	---------

	-----
	| X	|
	-----

*/
