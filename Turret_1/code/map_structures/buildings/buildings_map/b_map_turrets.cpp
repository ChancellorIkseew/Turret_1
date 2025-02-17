
#include "buildings_map.h"

#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "map_structures/team/team.h"


void BuildingsMap::setTurret(const BuildingType turretType, const TileCoord tile, Team* team)
{
	if (t1::bc::buildingsInfoTable.find(turretType) == t1::bc::buildingsInfoTable.end() || !buildingExists(tile) ||
		(buildingsMap[tile.x][tile.y]->getType() != BuildingType::STONE_TOWER && buildingsMap[tile.x][tile.y]->getType() != BuildingType::STEEL_TOWER))
	{
		return;
	}

	if (team->getBalance().isEnough(t1::bc::buildingsInfoTable[turretType].costToBuild))
	{
		team->getBalance().waste(t1::bc::buildingsInfoTable[turretType].costToBuild);
		buildingsMap[tile.x][tile.y]->setTurret(turretType);
	}
}

void BuildingsMap::removeTurret(const TileCoord tile)
{
	buildingsMap[tile.x][tile.y]->removeTurret();
}

bool BuildingsMap::isTurretOnTile(const TileCoord tile) const
{
	if (!buildingExists(tile))
		return false;
	return buildingsMap[tile.x][tile.y]->isTurretOnTower();
}
