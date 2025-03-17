
#include "buildings_map.h"

#include "map_structures/buildings/building/building.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "map_structures/team/team.h"

#define info t1::bc::buildingsInfoTable

static inline bool isCore(const BuildingType type) {
	return type >= BuildingType::CORE_MK1 && type <= BuildingType::CORE_MK3;
}

void BuildingsMap::createAuxilary(const uint8_t size, const TileCoord mainTile, Team* team)
{
	for (uint8_t i = 1; i < size; i++)
	{
		TileCoord tile = mainTile + t1::be::coordSquareArr[i];
		buildingsMap[tile.x][tile.y] = Building::createBuilding(BuildingType::AUXILARY, 0, mainTile, team);
		justChangedTiles.push_back(tile);
	}
}


void BuildingsMap::constructBuilding(const BuildingType type, const char direction, const TileCoord tile, Team* team)
{
	if (!info.count(type)) // not contains
		return;
	if (!team->getBalance().isEnough(info[type].costToBuild))
		return;
	if (placeBuilding(type, direction, tile, team))
		team->getBalance().waste(info[type].costToBuild);
}


bool BuildingsMap::placeBuilding(const BuildingType type, const char direction, const TileCoord tile, Team* team)
{
	if (!isAvaluablePlaceBuilding(type, tile, team))
		return false;
	auto building = Building::createBuilding(type, direction, tile, team);
	buildingsMap[tile.x][tile.y] = building;
	createAuxilary(info[type].size, tile, team);
	justChangedTiles.push_back(tile);
	if (isCore(type))
		cores.emplace_back(building);
	return true;
}


bool BuildingsMap::isAvaluablePlaceBuilding(const BuildingType type, const TileCoord tile, Team* team) const
{
	uint8_t size = info[type].size;
	for (uint8_t i = 0; i < size; i++) // cheeck_square_for_place
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
	const TileCoord mainTile = getBuildingMainTileCoord(tile);
	const uint8_t size = buildingsMap[mainTile.x][mainTile.y]->getSize();
	const BuildingType type = buildingsMap[mainTile.x][mainTile.y]->getType();
	for (uint8_t i = 0; i < size; ++i)
	{
		TileCoord iTile = mainTile + t1::be::coordSquareArr[i];
		buildingsMap[iTile.x][iTile.y].reset();
		justChangedTiles.push_back(iTile);
	}
	if (!isCore(type))
		return;
	const auto it = std::remove_if(cores.begin(), cores.end(), [&](const auto& core) { return core->getTileCoord() == mainTile; });
	cores.erase(it, cores.end());
}
