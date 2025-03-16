
#include "buildings_map.h"

#include "map_structures/team/team.h"
#include "map_structures/buildings/building/building.h"
#include "map_structures/buildings/building/buildings_enum.h"

void BuildingsMap::setDamage(const float damage, const TileCoord tile)
{
	setDamage(static_cast<int16_t>(damage), tile);
}

void BuildingsMap::setDamage(const int16_t damage, const TileCoord tile)
{
	if (!buildingExists(tile))
		return;
	TileCoord mainBuilding = getBuildingMainTileCoord(tile);
	buildingsMap[mainBuilding.x][mainBuilding.y]->setDamage(damage);
	if (buildingsMap[mainBuilding.x][mainBuilding.y]->getDurability() < 1)
		demolishBuilding(mainBuilding);
}


TileCoord BuildingsMap::getBuildingMainTileCoord(const TileCoord tile) const
{
	if (!buildingExists(tile))
		return INCORRECT_TILE_COORD;
	return buildingsMap[tile.x][tile.y]->getTileCoord();
}


void BuildingsMap::setBuildingDurability(const int16_t durability, const TileCoord tile)
{
	if (!buildingExists(tile))
		return;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	buildingsMap[mainTile.x][mainTile.y]->setDurability(durability);
}

short BuildingsMap::getBuildingDurability(const TileCoord tile) const
{
	if (!buildingExists(tile))
		return 0;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->getDurability();
}

char BuildingsMap::getBuildingDirection(const TileCoord tile) const
{
	if (buildingExists(tile))
		return buildingsMap[tile.x][tile.y]->getDirection();
	return 0;
}

Team* BuildingsMap::getTeam(const TileCoord tile) const
{
	if (buildingExists(tile))
		return buildingsMap[tile.x][tile.y]->getTeam();
	return nullptr;
}

int BuildingsMap::getTeamID(const TileCoord tile) const
{
	if (buildingExists(tile))
		return buildingsMap[tile.x][tile.y]->getTeamID();
	return 199999;
}

BuildingType BuildingsMap::getBuildingType(const TileCoord tile) const
{
	if (!buildingExists(tile))
		return BuildingType::VOID_;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->getType();
}
