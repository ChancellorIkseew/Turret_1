
#include "path_finding.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/building.h"
#include "map_structures/blueprints/blueprints_map.h"
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


TileCoord PathFinding::findNextTile(const TileCoord point, const TileCoord aim, const BuildingsMap& buildingsMap)
{
	const int currentDistance = pow2i(point.x - aim.x) + pow2i(point.y - aim.y); // SQR(real_distance)
	int newDistance = 0;

	for (int i = 1; i < 5; i++) // [0](0,0); [1](-1,0); [2](0,-1); [3](0,1); [4](1,0)
	{
		TileCoord cheekTile = point + coordSpyralArr[i];
		if (!buildingsMap.isVoidBuilding(cheekTile))
			continue;

		newDistance = pow2i(cheekTile.x - aim.x) + pow2i(cheekTile.y - aim.y); // SQR(real_distance)
		if (newDistance < currentDistance)
			return cheekTile;
	}
	return point;
}


TileCoord PathFinding::findClosestCore(const TileCoord point, const BuildingsMap& buildingsMap)
{
	const std::vector<std::shared_ptr<Building>>& cores = buildingsMap.getCores();
	if (cores.size() == 0)
		return INCORRECT_TILE_COORD; // возможны изменения

	int distance = 0;
	int minDistance = MAX_EXPECTED_DISTANCE;
	int index = 0;
	TileCoord coreCenter;
	for (int i = 0; i < cores.size(); ++i)
	{
		coreCenter = findBuildingCenter(*cores[i]);
		distance = pow2i(point.x - coreCenter.x) + pow2i(point.y - coreCenter.y); // SQR(real_distance)
		if (distance < minDistance)
		{
			minDistance = distance;
			index = i;
		}
	}

	return findBuildingCenter(*cores[index]);
}

constexpr int SPYRAL_RANGE = 4109;
TileCoord PathFinding::findClosestBlueprint(const TileCoord point, const BlueprintsMap& blueprintsMap)
{;
	TileCoord checkTile;
	for (int i = 0; i < SPYRAL_RANGE; i++)
	{
		checkTile = point + coordSpyralArr[i];
		if (blueprintsMap.isFilledTile(checkTile))
			return checkTile;
	}
	return INCORRECT_TILE_COORD;
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
