
#include "buildings_map.h"

#include "map_structures/buildings/building/building.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "map_structures/team/team.h"


void BuildingsMap::createAuxilary(const short size, const TileCoord mainTile, Team* team)
{
	for (int i = 1; i < size; i++)
	{
		TileCoord tile = mainTile + t1::be::coordSquareArr[i];
		buildingsMap[tile.x][tile.y] = Building::createBuilding(BuildingType::AUXILARY, 0, mainTile, team);
	}
}


void BuildingsMap::constructBuilding(const BuildingType type, const char direction, const TileCoord tile, Team* team)
{
	if (t1::bc::buildingsInfoTable.find(type) == t1::bc::buildingsInfoTable.end())
		return;

	if (team->getBalance().isEnough(t1::bc::buildingsInfoTable[type].costToBuild))
	{
		if (placeBuilding(type, direction, tile, team))
			team->getBalance().waste(t1::bc::buildingsInfoTable[type].costToBuild);
	}
}


bool BuildingsMap::placeBuilding(const BuildingType type, const char direction, const TileCoord tile, Team* team)
{
	if (!isAvaluablePlaceBuilding(type, tile, team))
		return false;
	auto building = Building::createBuilding(type, direction, tile, team);
	buildingsMap[tile.x][tile.y] = building;
	int size = t1::bc::buildingsInfoTable[type].size;
	createAuxilary(size, tile, team);
	if (type == BuildingType::CORE_MK1 || type == BuildingType::CORE_MK2 || type == BuildingType::CORE_MK3)
		cores.emplace_back(building);
	justChangedTiles.push_back(tile);
	return true;
}


bool BuildingsMap::isAvaluablePlaceBuilding(const BuildingType type, const TileCoord tile, Team* team) const
{
	int size = t1::bc::buildingsInfoTable[type].size;
	for (int i = 0; i < size; i++) // cheeck_square_for_place
	{
		TileCoord cheekTile = tile + t1::be::coordSquareArr[i];
		if (!isVoidBuilding(cheekTile))
			return false;
	}
	return true;
}


void BuildingsMap::demolishBuilding(const TileCoord tile)
{
	if (!buildingExists(tile))
		return;
	TileCoord mainBuilding = getBuildingMainTileCoord(tile);
	BuildingType type = buildingsMap[mainBuilding.x][mainBuilding.y]->getType();
	short size = buildingsMap[mainBuilding.x][mainBuilding.y]->getSize();
	for (int i = 0; i < size; ++i)
	{
		TileCoord iTile = mainBuilding + t1::be::coordSquareArr[i];
		buildingsMap[iTile.x][iTile.y].reset();
		justChangedTiles.push_back(iTile);
	}
	if (type == BuildingType::CORE_MK1 || type == BuildingType::CORE_MK2 || type == BuildingType::CORE_MK3)
	{
		for (auto core = cores.begin(); core != cores.end(); ++core)
		{
			if ((*core)->getTileCoord().x == mainBuilding.x && (*core)->getTileCoord().y == mainBuilding.y)
			{
				cores.erase(core);
				return;
			}
		}
	}
}
