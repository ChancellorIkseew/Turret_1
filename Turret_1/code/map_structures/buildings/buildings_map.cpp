
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


void BuildingsMap::constructBuilding(int buildingType, char direction, int tileX, int tileY)
{
	int size = g_BuildingsInfoArray[buildingType].size;
	int durability = g_BuildingsInfoArray[buildingType].durability * PreSettings::getBuildingsMaxDurabilityModidier();

	for (int i = 0; i < size; i++) // cheeck_square_for_building
	{
		if (tileX + coordSquareArr[i].x < 0 || tileX + coordSquareArr[i].x >= mapMaxX || 
			tileY + coordSquareArr[i].y < 0 || tileY + coordSquareArr[i].y >= mapMaxY)
		{
			return;
		}

		if (buildingsMap[tileX + coordSquareArr[i].x][tileY + coordSquareArr[i].y] != nullptr)
		{
			return;
		}
	}

	if (isEnoughAllRes(g_BuildingsInfoArray[buildingType].costToBuild))
	{
		wasteRes(g_BuildingsInfoArray[buildingType].costToBuild);
		buildingsMap[tileX][tileY] = Building::setBuilding(buildingType, direction, durability, size, tileX, tileY);

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


void BuildingsMap::demolishBuilding(int tileX, int tileY)
{
	if (buildingsMap[tileX][tileY]->type != bType::AUXILARY)
	{
		if (buildingsMap[tileX][tileY]->size != 1)
		{
			for (int i = 1; i < buildingsMap[tileX][tileY]->size; i++)
			{
				buildingsMap[tileX + coordSquareArr[i].x][tileY + coordSquareArr[i].y] = nullptr;
			}
		}

		delete buildingsMap[tileX][tileY];
		buildingsMap[tileX][tileY] = nullptr;

		isMapChanged = true;
	}
	else
	{
		TileCoord mainBuilding = getBuildingMainTileCoord(tileX, tileY);
		demolishBuilding(mainBuilding.x, mainBuilding.y);
	}
}


bool BuildingsMap::buildingExists(int tileX, int tileY)
{
	return (tileX >= 0 && tileX < mapMaxX && tileY >= 0 && tileY < mapMaxY &&
		buildingsMap[tileX][tileY] != nullptr);
}


void BuildingsMap::setDamage(short damage, int tileX, int tileY)
{
	if (!buildingExists(tileX, tileY))
	{
		return;
	}

	if (buildingsMap[tileX][tileY]->type != AUXILARY)
	{
		buildingsMap[tileX][tileY]->durability = buildingsMap[tileX][tileY]->durability - damage;

		if (buildingsMap[tileX][tileY]->durability < 1)
		{
			demolishBuilding(tileX, tileY);
		}
	}
	else
	{
		TileCoord mainBuilding = getBuildingMainTileCoord(tileX, tileY);
		setDamage(damage, mainBuilding.x, mainBuilding.y);
	}

}


TileCoord BuildingsMap::getBuildingMainTileCoord(int tileX, int tileY)
{
	for (int i = 0; i < buildingsMap[tileX][tileY]->size; ++i)
	{
		if (buildingsMap[tileX - coordSquareArr[i].x][tileY - coordSquareArr[i].y]->size == buildingsMap[tileX][tileY]->size &&
			buildingsMap[tileX - coordSquareArr[i].x][tileY - coordSquareArr[i].y]->type != AUXILARY)
		{
			return { tileX - coordSquareArr[i].x , tileY - coordSquareArr[i].y };
		}
	}
	return {0,0};
}


void BuildingsMap::setBuildingDurability(short durability, int tileX, int tileY)
{
	if (buildingExists(tileX, tileY))
		buildingsMap[tileX][tileY]->durability = durability;
}

void BuildingsMap::setBuildingType(char type, int tileX, int tileY)
{
	if (buildingExists(tileX, tileY))
		buildingsMap[tileX][tileY]->type = type;
}

char BuildingsMap::getBuildingType(int tileX, int tileY) 
{
	if (!buildingExists(tileX, tileY))
	{
		return VOID_;
	}
	return buildingsMap[tileX][tileY]->type; 
}

short BuildingsMap::getBuildingDurability(int tileX, int tileY) 
{ 
	if (!buildingExists(tileX, tileY))
	{
		return 0;
	}
	return buildingsMap[tileX][tileY]->durability; 
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



void BuildingsMap::addToInventory(int resType, int tileX, int tileY)
{
	TileCoord mainTile = getBuildingMainTileCoord(tileX, tileY);

	buildingsMap[mainTile.x][mainTile.y]->addToInventory(resType, 1);
}



bool BuildingsMap::isThisPositionFree(int tileX, int tileY, int position)
{
	if (buildingsMap[tileX][tileY]->type != AUXILARY)
	{
		return buildingsMap[tileX][tileY]->isThisPositionFree(position);
	}
	else
	{
		TileCoord mainTile = getBuildingMainTileCoord(tileX, tileY);

		return buildingsMap[mainTile.x][mainTile.y]->isThisPositionFree(position);
	}
}

void BuildingsMap::leavePosition(int tileX, int tileY, int position)
{
	buildingsMap[tileX][tileY]->leavePosition(position);
}

void BuildingsMap::takePosition(int tileX, int tileY, int position)
{
	buildingsMap[tileX][tileY]->takePosition(position);
}

bool BuildingsMap::canAccept(int resType, int tileX, int tileY)
{
	if (!buildingExists(tileX, tileY))
	{
		return false;
	}

	if (buildingsMap[tileX][tileY]->type != AUXILARY)
	{
		return buildingsMap[tileX][tileY]->canAccept(resType);
	}
	else
	{
		TileCoord mainTile = getBuildingMainTileCoord(tileX, tileY);

		return buildingsMap[mainTile.x][mainTile.y]->canAccept(resType);
	}
}




int BuildingsMap::getBuildingMainTileType(int tileX, int tileY)
{
	for (int i = 1; i < buildingsMap[tileX][tileY]->size; ++i)
	{
		if (buildingsMap[tileX - coordSquareArr[i].x][tileY - coordSquareArr[i].y]->size == buildingsMap[tileX][tileY]->size &&
			buildingsMap[tileX - coordSquareArr[i].x][tileY - coordSquareArr[i].y]->type != AUXILARY)
		{
			return buildingsMap[tileX - coordSquareArr[i].x][tileY - coordSquareArr[i].y]->type;
		}
	}

	return VOID_;
}



void BuildingsMap::setTurret(int turretType, int tileX, int tileY)
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

void BuildingsMap::removeTurret(int tileX, int tileY)
{
	buildingsMap[tileX][tileY]->removeTurret();
}

bool BuildingsMap::isTurretOnTile(int tileX, int tileY)
{
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
