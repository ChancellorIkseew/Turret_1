
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>


#include "buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/buildings/building/buildings_info.h"

#include "game_interface/gameplay/gameplay_util/camera.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/base_engine/tile_coord.h"
#include "map_structures/team/team.h"


BuildingsMap::BuildingsMap(const TileCoord mapSize)
{
	this->mapSize = mapSize;

	buildingsMap.resize(mapSize.x);
	buildingsMap.reserve(mapSize.x);
	for (auto& line : buildingsMap)
	{
		line.resize(mapSize.y);
		line.reserve(mapSize.y);
		for (auto& building : line)
		{
			building = nullptr;
		}
	}

	isMapChanged = false;
}

BuildingsMap::~BuildingsMap()
{
	buildingsMap.clear();
}


void BuildingsMap::loadMap(const std::string& folder)
{
	/*
	std::string file = "saves/" + folder + "/buildings.txt";
	std::ifstream fin;
	fin.open(file);
	if (fin.is_open())
	{
		while (true)
		{
			char nextSymbol;
			fin >> nextSymbol;
			if (nextSymbol == '&')
				break;
			
			fin.seekg(-1, std::ios::cur);
			TileCoord tile = { 0, 0 };
			int type;
			fin >> tile.x >> tile.y >> type;
			buildingsMap[tile.x][tile.y] = Building::createBuilding(type, 0, 0, 0, tile, team);
			buildingsMap[tile.x][tile.y]->load(fin);
			createAuxilary(buildingsMap[tile.x][tile.y]->getSize(), tile, team);
		}
	}
	fin.close();
	isMapChanged = true;
	std::cout << "sucñessfull_buildings_map_load" << '\n';
	*/
}


void BuildingsMap::saveMap(const std::string& folder)
{
	std::string file = "saves/" + folder + "/buildings.txt";
	std::ofstream fout;
	fout.open(file);
	if (fout.is_open())
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			for (int y = 0; y < mapSize.y; y++)
			{
				if (buildingsMap[x][y] != nullptr && buildingsMap[x][y]->getType() != AUXILARY)
				{
					fout << x << " " << y << " " << buildingsMap[x][y]->getType() << '\n';
					buildingsMap[x][y]->save(fout);
				}
			}
		}
		fout << '&';
	}
	fout.close();
	std::cout << "Save_buildings_map_works" <<'\n';
}


void BuildingsMap::createAuxilary(const short size, const TileCoord tile, Team* team)
{
	for (int i = 1; i < size; i++)
	{
		int iTileX = tile.x + t1::be::coordSquareArr[i].x;
		int iTileY = tile.y + t1::be::coordSquareArr[i].y;
		buildingsMap[iTileX][iTileY] = Building::createBuilding(AUXILARY, 0, 0, size, tile, team);
	}
}


void BuildingsMap::constructBuilding(const int type, const char direction, const TileCoord tile, Team* team)
{
	if (t1::bc::buildingsInfoTable.find(type) == t1::bc::buildingsInfoTable.end())
		return;

	int size = t1::bc::buildingsInfoTable[type].size;
	int durability = t1::bc::buildingsInfoTable[type].durability * PreSettings::getBuildings().maxDurabilityModifier;

	for (int i = 0; i < size; i++) // cheeck_square_for_building
	{
		int iTileX = tile.x + t1::be::coordSquareArr[i].x;
		int iTileY = tile.y + t1::be::coordSquareArr[i].y;
		if (!isVoidBuilding(iTileX, iTileY))
			return;
	}

	if (team->getBalance().isEnough(t1::bc::buildingsInfoTable[type].costToBuild))
	{
		team->getBalance().waste(t1::bc::buildingsInfoTable[type].costToBuild);
		buildingsMap[tile.x][tile.y] = Building::createBuilding(type, direction, durability, size, tile, team);
		createAuxilary(size, tile, team);
		isMapChanged = true;
	}
}


void BuildingsMap::demolishBuilding(const TileCoord tile)
{
	if (!buildingExists(tile))
		return;
	TileCoord mainBuilding = getBuildingMainTileCoord(tile);
	short size = buildingsMap[mainBuilding.x][mainBuilding.y]->getSize();
	for (int i = 0; i < size; ++i)
	{
		int iTileX = mainBuilding.x + t1::be::coordSquareArr[i].x;
		int iTileY = mainBuilding.y + t1::be::coordSquareArr[i].y;

		buildingsMap[iTileX][iTileY].reset();
	}
	isMapChanged = true;
}


bool BuildingsMap::buildingExists(const int tileX, const int tileY)
{
	return (tileX >= 0 && tileX < mapSize.x && tileY >= 0 && tileY < mapSize.y &&
		buildingsMap[tileX][tileY] != nullptr);
}

bool BuildingsMap::isVoidBuilding(const int tileX, const int tileY)
{
	return (tileX >= 0 && tileX < mapSize.x && tileY >= 0 && tileY < mapSize.y &&
		buildingsMap[tileX][tileY] == nullptr);
}

bool BuildingsMap::buildingExists(const TileCoord tile)
{
	return buildingExists(tile.x, tile.y);
}

bool BuildingsMap::isVoidBuilding(const TileCoord tile)
{
	return isVoidBuilding(tile.x, tile.y);
}


void BuildingsMap::setDamage(const short damage, const TileCoord tile)
{
	if (!buildingExists(tile))
		return;
	TileCoord mainBuilding = getBuildingMainTileCoord(tile);
	buildingsMap[mainBuilding.x][mainBuilding.y]->setDamage(damage);
	if (buildingsMap[mainBuilding.x][mainBuilding.y]->getDurability() < 1)
	{
		demolishBuilding(mainBuilding);
	}
}


TileCoord BuildingsMap::getBuildingMainTileCoord(const TileCoord tile)
{
	if (!buildingExists(tile))
		return {-1,-1};
	return buildingsMap[tile.x][tile.y]->getTileCoord();
}


void BuildingsMap::setBuildingDurability(const short durability, const TileCoord tile)
{
	if (!buildingExists(tile))
		return;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	buildingsMap[mainTile.x][mainTile.y]->setDurability(durability);
}

short BuildingsMap::getBuildingDurability(const TileCoord tile)
{ 
	if (!buildingExists(tile))
		return 0;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->getDurability();
}

char BuildingsMap::getBuildingDirection(const TileCoord tile)
{
	if (buildingExists(tile))
		return buildingsMap[tile.x][tile.y]->getDirection();
	return 0;
}

Team* BuildingsMap::getTeam(const TileCoord tile)
{
	if (buildingExists(tile))
		return buildingsMap[tile.x][tile.y]->getTeam();
	return nullptr;
}

int BuildingsMap::getTeamID(const TileCoord tile)
{
	if (buildingExists(tile))
		return buildingsMap[tile.x][tile.y]->getTeamID();
	return 199999;
}

bool BuildingsMap::getIsMapChanged() { return isMapChanged; }
void BuildingsMap::cleanMapChanged() { isMapChanged = false; }


void BuildingsMap::intetractMap()
{
	for (auto& line : buildingsMap)
	{
		for (auto& building : line)
		{
			if (building != nullptr && building->getType() != AUXILARY)
			{
				building->interact();
			}
		}
	}
}


void BuildingsMap::addToInventory(const uint16_t resType, const TileCoord tile)
{
	if (!buildingExists(tile))
		return;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	buildingsMap[mainTile.x][mainTile.y]->addToInventory(resType, 1);
}

void BuildingsMap::addToInventory(ResourceUnit& unit, const TileCoord tile)
{
	if (!buildingExists(tile))
		return;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	buildingsMap[mainTile.x][mainTile.y]->addToInventory(unit);
}

bool BuildingsMap::canAccept(const uint16_t resType, const TileCoord tile)
{
	if (!buildingExists(tile))
		return false;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->canAccept(resType);
}

bool BuildingsMap::canAccept(const ResourceUnit& unit, const TileCoord tile)
{
	if (!buildingExists(tile))
		return false;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->canAccept(unit);
}


int BuildingsMap::getBuildingType(const TileCoord tile)
{
	if (!buildingExists(tile))
		return VOID_;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->getType();
}


void BuildingsMap::setTurret(const int turretType, const TileCoord tile, Team* team)
{
	if (t1::bc::buildingsInfoTable.find(turretType) == t1::bc::buildingsInfoTable.end() || !buildingExists(tile) ||
		(buildingsMap[tile.x][tile.y]->getType() != STONE_TOWER && buildingsMap[tile.x][tile.y]->getType() != STEEL_TOWER))
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

bool BuildingsMap::isTurretOnTile(const TileCoord tile)
{
	if (!buildingExists(tile))
		return false;
	return buildingsMap[tile.x][tile.y]->isTurretOnTower();
}


void BuildingsMap::drawMap(sf::RenderWindow& window)
{
	int startX = Camera::startTile.x;
	int startY = Camera::startTile.y;

	int endX = Camera::endTile.x;
	int endY = Camera::endTile.y;

	for (int x = startX; x < endX; ++x)
	{
		for (int y = startY; y < endY; ++y)
		{
			if (buildingsMap[x][y] != nullptr && buildingsMap[x][y]->getType() != AUXILARY)
			{
				buildingsMap[x][y]->draw(window);
			}
		}
	}
}
