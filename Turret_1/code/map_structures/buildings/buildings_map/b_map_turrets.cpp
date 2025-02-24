
#include "buildings_map.h"

#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "map_structures/team/team.h"
#include "map_structures/buildings/building_types/walls/tower.h"


void BuildingsMap::setTurret(const BuildingType turretType, const TileCoord tile, Team* team)
{
	if (t1::bc::buildingsInfoTable.find(turretType) == t1::bc::buildingsInfoTable.end() || !buildingExists(tile) ||
		(buildingsMap[tile.x][tile.y]->getType() != BuildingType::STONE_TOWER && buildingsMap[tile.x][tile.y]->getType() != BuildingType::STEEL_TOWER))
		return;

	if (team->getBalance().isEnough(t1::bc::buildingsInfoTable[turretType].costToBuild))
	{
		team->getBalance().waste(t1::bc::buildingsInfoTable[turretType].costToBuild);
		Tower* tower = static_cast<Tower*>(buildingsMap[tile.x][tile.y].get());
		tower->setTurret(turretType);
	}
}

void BuildingsMap::removeTurret(const TileCoord tile)
{
	Tower* tower = static_cast<Tower*>(buildingsMap[tile.x][tile.y].get());
	tower->removeTurret();
}

bool BuildingsMap::isTurretOnTile(const TileCoord tile) const
{
	if (!buildingExists(tile))
		return false;
	if (buildingsMap[tile.x][tile.y]->getType() != BuildingType::STONE_TOWER)
		return false;
	const Tower* tower = static_cast<const Tower*>(buildingsMap[tile.x][tile.y].get());
	return tower->isTurretOnTower();
}
