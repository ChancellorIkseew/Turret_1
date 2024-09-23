
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>


#include "buildings_map.h"
#include "building/buildings_enum.h"
#include "building/buildings_info.h"

#include "game_interface/gameplay/gameplay_util/camera.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/base_engine/tile_coord.h"
#include "map_structures/resources/resources.h"


BuildingsMap::BuildingsMap(std::string saveFolderName)
{
	mapMaxX = PreSettings::getMapMaxX();
	mapMaxY = PreSettings::getMapMaxY();

	buildingsMap.resize(mapMaxX);
	buildingsMap.reserve(mapMaxX);
	for (int x = 0; x < mapMaxX; ++x)
	{
		buildingsMap[x].resize(mapMaxY);
		buildingsMap[x].reserve(mapMaxY);
		for (int y = 0; y < mapMaxY; ++y)
		{
			buildingsMap[x][y] = nullptr;
		}
	}

	saveFileName = "saves/" + saveFolderName + "/buildings.txt";
	isMapChanged = false;
}

BuildingsMap::~BuildingsMap()
{
	for (int x = 0; x < mapMaxX; ++x)
	{
		for (int y = 0; y < mapMaxY; ++y)
		{
			if (buildingsMap[x][y] != nullptr)
			{
				delete buildingsMap[x][y];
				buildingsMap[x][y] = nullptr;
			}
		}
	}
}


void BuildingsMap::generateMap()
{
	delete buildingsMap[48][48];
	buildingsMap[48][48] = Building::setBuilding(CORE_MK1, '0', 900, 16, 48, 48);
	
	for (int i = 1; i < 16; i++)
	{
		buildingsMap[48 + coordSquareArr[i].x][48 + coordSquareArr[i].y] = Building::setBuilding(AUXILARY, 0, 0, 16, 0, 0);
	}
	
	isMapChanged = true;
}


void BuildingsMap::loadMap()
{
	std::ifstream fin;
	fin.open(saveFileName);
	if (fin.is_open())
	{
		for (int y = 0; y < mapMaxY; y++)
		{
			for (int x = 0; x < mapMaxX; x++)
			{
				int bType;
				fin >> bType;
				buildingsMap[x][y] = Building::createBuilding(bType);
				buildingsMap[x][y]->load(fin);
			}
		}
	}
	fin.close();
	isMapChanged = true;
	std::cout << "sucñessfull_buildings_map_load" << '\n';
}


void BuildingsMap::saveMap()
{
	std::ofstream fout;
	fout.open(saveFileName);
	if (fout.is_open())
	{
		for (int y = 0; y < mapMaxY; y++)
		{
			for (int x = 0; x < mapMaxX; x++)
			{
				if (buildingsMap[x][y] != nullptr)
				{
					buildingsMap[x][y]->save(fout);
				}
			}
		}
	}
	fout.close();
	std::cout << "Save_buildings_map_works" <<'\n';
}


void BuildingsMap::constructBuilding(const int type, const char direction, const int tileX, const int tileY)
{
	int size = g_BuildingsInfoArray[type].size;
	int durability = g_BuildingsInfoArray[type].durability * PreSettings::getBuildingsMaxDurabilityModidier();

	for (int i = 0; i < size; i++) // cheeck_square_for_building
	{
		int iTileX = tileX - coordSquareArr[i].x;
		int iTileY = tileY - coordSquareArr[i].y;

		if (iTileX < 0 || iTileX >= mapMaxX || iTileY < 0 || iTileY >= mapMaxY ||
			buildingsMap[iTileX][iTileY] != nullptr)
		{
			return;
		}
	}

	if (isEnoughAllRes(g_BuildingsInfoArray[type].costToBuild))
	{
		wasteRes(g_BuildingsInfoArray[type].costToBuild);
		buildingsMap[tileX][tileY] = Building::setBuilding(type, direction, durability, size, tileX, tileY);

		if (size > 1)
		{
			for (int i = 1; i < size; i++)
			{
				buildingsMap[tileX + coordSquareArr[i].x][tileY + coordSquareArr[i].y] = Building::setBuilding(AUXILARY, 0, 0, size, tileX, tileY);
			}
		}
		isMapChanged = true;
	}
}


void BuildingsMap::demolishBuilding(const int tileX, const int tileY)
{
	if (!buildingExists(tileX, tileY))
		return;
	TileCoord mainBuilding = getBuildingMainTileCoord(tileX, tileY);
	short size = buildingsMap[mainBuilding.x][mainBuilding.y]->size;
	for (int i = 0; i < size; ++i)
	{
		int iTileX = mainBuilding.x - coordSquareArr[i].x;
		int iTileY = mainBuilding.y - coordSquareArr[i].y;

		delete buildingsMap[iTileX][iTileY];
		buildingsMap[iTileX][iTileY] = nullptr;
	}
	isMapChanged = true;
}


bool BuildingsMap::buildingExists(const int tileX, const int tileY)
{
	return (tileX >= 0 && tileX < mapMaxX && tileY >= 0 && tileY < mapMaxY &&
		buildingsMap[tileX][tileY] != nullptr);
}


void BuildingsMap::setDamage(const short damage, const int tileX, const int tileY)
{
	if (!buildingExists(tileX, tileY))
		return;
	TileCoord mainBuilding = getBuildingMainTileCoord(tileX, tileY);
	buildingsMap[mainBuilding.x][mainBuilding.y]->setDamage(damage);
	if (buildingsMap[mainBuilding.x][mainBuilding.y]->durability < 1)
	{
		demolishBuilding(mainBuilding.x, mainBuilding.y);
	}
}


TileCoord BuildingsMap::getBuildingMainTileCoord(const int tileX, const int tileY)
{
	for (int i = 0; i < buildingsMap[tileX][tileY]->size; ++i)
	{
		int iTileX = tileX - coordSquareArr[i].x;
		int iTileY = tileY - coordSquareArr[i].y;

		if (buildingsMap[iTileX][iTileY] != nullptr && buildingsMap[iTileX][iTileY]->type != AUXILARY &&
			buildingsMap[iTileX][iTileY]->size == buildingsMap[tileX][tileY]->size)
		{
			return { tileX, tileY};
		}
	}
	return {-1,-1};
}


void BuildingsMap::setBuildingDurability(const short durability, const int tileX, const int tileY)
{
	if (!buildingExists(tileX, tileY))
		return;
	TileCoord mainTile = getBuildingMainTileCoord(tileX, tileY);
	buildingsMap[mainTile.x][mainTile.y]->durability = durability;
}

short BuildingsMap::getBuildingDurability(const int tileX, const int tileY)
{ 
	if (!buildingExists(tileX, tileY))
		return 0;
	TileCoord mainTile = getBuildingMainTileCoord(tileX, tileY);
	return buildingsMap[mainTile.x][mainTile.y]->durability;
}

bool BuildingsMap::getIsMapChanged() { return isMapChanged; }
void BuildingsMap::cleanMapChanged() { isMapChanged = false; }


void BuildingsMap::intetractMap()
{
	for (int y = 0; y < mapMaxY; ++y)
	{
		for (int x = 0; x < mapMaxX; ++x)
		{
			if (buildingsMap[x][y] != nullptr && buildingsMap[x][y]->type != AUXILARY)
			{
				buildingsMap[x][y]->interact();
			}
		}
	}
}


void BuildingsMap::addToInventory(const int resType, const int tileX, const int tileY)
{
	TileCoord mainTile = getBuildingMainTileCoord(tileX, tileY);
	buildingsMap[mainTile.x][mainTile.y]->addToInventory(resType, 1);
}


bool BuildingsMap::isThisPositionFree(const int tileX, const int tileY, const int position)
{
	if (!buildingExists(tileX, tileY))
		return false;
	TileCoord mainTile = getBuildingMainTileCoord(tileX, tileY);
	return buildingsMap[mainTile.x][mainTile.y]->isThisPositionFree(position);
}

void BuildingsMap::leavePosition(const int tileX, const int tileY, const int position)
{
	buildingsMap[tileX][tileY]->leavePosition(position);
}

void BuildingsMap::takePosition(const int tileX, const int tileY, const int position)
{
	buildingsMap[tileX][tileY]->takePosition(position);
}

bool BuildingsMap::canAccept(const int resType, const int tileX, const int tileY)
{
	if (!buildingExists(tileX, tileY))
		return false;
	TileCoord mainTile = getBuildingMainTileCoord(tileX, tileY);
	return buildingsMap[mainTile.x][mainTile.y]->canAccept(resType);
}


int BuildingsMap::getBuildingType(const int tileX, const int tileY)
{
	if (!buildingExists(tileX, tileY))
		return VOID_;
	TileCoord mainTile = getBuildingMainTileCoord(tileX, tileY);
	return buildingsMap[mainTile.x][mainTile.y]->type;
}


void BuildingsMap::setTurret(const int turretType, const int tileX, const int tileY)
{
	if (!buildingExists(tileX, tileY) ||
		(buildingsMap[tileX][tileY]->type != STONE_TOWER && buildingsMap[tileX][tileY]->type != STEEL_TOWER))
	{
		return;
	}

	if (isEnoughAllRes(g_BuildingsInfoArray[turretType].costToBuild))
	{
		wasteRes(g_BuildingsInfoArray[turretType].costToBuild);
		buildingsMap[tileX][tileY]->setTurret(turretType);
	}
}

void BuildingsMap::removeTurret(const int tileX, const int tileY)
{
	buildingsMap[tileX][tileY]->removeTurret();
}

bool BuildingsMap::isTurretOnTile(const int tileX, const int tileY)
{
	if (!buildingExists(tileX, tileY))
		return false;
	return buildingsMap[tileX][tileY]->isTurretOnTower();
}


void BuildingsMap::drawMap(sf::RenderWindow& window)
{
	int startX = Camera::startTile.x;
	int startY = Camera::startTile.y;

	int endX = Camera::endTile.x;
	int endY = Camera::endTile.y;

	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			if (buildingsMap[x][y] != nullptr && buildingsMap[x][y]->type != AUXILARY)
			{
				buildingsMap[x][y]->draw(window);
			}
		}
	}
}
