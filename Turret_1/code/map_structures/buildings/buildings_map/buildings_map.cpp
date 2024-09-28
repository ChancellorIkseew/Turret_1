
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
#include "map_structures/resources/resources.h"


BuildingsMap::BuildingsMap(const TileCoord mapSize)
{
	mapSizeX = mapSize.x;
	mapSizeY = mapSize.y;

	buildingsMap.resize(mapSizeX);
	buildingsMap.reserve(mapSizeX);
	for (int x = 0; x < mapSizeX; ++x)
	{
		buildingsMap[x].resize(mapSizeY);
		buildingsMap[x].reserve(mapSizeY);
		for (int y = 0; y < mapSizeY; ++y)
		{
			buildingsMap[x][y] = nullptr;
		}
	}

	isMapChanged = false;
}

BuildingsMap::~BuildingsMap()
{
	buildingsMap.clear();
}


void BuildingsMap::generateMap()
{
	buildingsMap[48][48] = Building::createBuilding(CORE_MK1, '0', 900, 16, { 48, 48 });
	createAuxilary(16, { 48, 48 });
	isMapChanged = true;
}


void BuildingsMap::loadMap(const std::string& folder)
{
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
			TileCoord tile;
			int type;
			fin >> tile.x >> tile.y >> type;
			buildingsMap[tile.x][tile.y] = Building::createBuilding(type, 0, 0, 0, tile);
			buildingsMap[tile.x][tile.y]->load(fin);
			createAuxilary(buildingsMap[tile.x][tile.y]->getSize(), tile);
		}
	}
	fin.close();
	isMapChanged = true;
	std::cout << "sucñessfull_buildings_map_load" << '\n';
}


void BuildingsMap::saveMap(const std::string& folder)
{
	std::string file = "saves/" + folder + "/buildings.txt";
	std::ofstream fout;
	fout.open(file);
	if (fout.is_open())
	{
		for (int x = 0; x < mapSizeX; x++)
		{
			for (int y = 0; y < mapSizeY; y++)
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


void BuildingsMap::createAuxilary(const short size, const TileCoord tile)
{
	for (int i = 1; i < size; i++)
	{
		int iTileX = tile.x + t1::be::coordSquareArr[i].x;
		int iTileY = tile.y + t1::be::coordSquareArr[i].y;
		buildingsMap[iTileX][iTileY] = Building::createBuilding(AUXILARY, 0, 0, size, tile);
	}
}


void BuildingsMap::constructBuilding(const int type, const char direction, const TileCoord tile)
{
	int size = g_BuildingsInfoArray[type].size;
	int durability = g_BuildingsInfoArray[type].durability * PreSettings::getBuildingsMaxDurabilityModidier();

	for (int i = 0; i < size; i++) // cheeck_square_for_building
	{
		int iTileX = tile.x + t1::be::coordSquareArr[i].x;
		int iTileY = tile.y + t1::be::coordSquareArr[i].y;
		if (!isVoidBuilding(iTileX, iTileY))
			return;
	}

	if (t1::res::isEnoughAllRes(g_BuildingsInfoArray[type].costToBuild))
	{
		t1::res::wasteRes(g_BuildingsInfoArray[type].costToBuild);
		buildingsMap[tile.x][tile.y] = Building::createBuilding(type, direction, durability, size, tile);
		createAuxilary(size, tile);
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
		buildingsMap[iTileX][iTileY] = nullptr;
	}
	isMapChanged = true;
}


inline bool BuildingsMap::buildingExists(const int tileX, const int tileY)
{
	return (tileX >= 0 && tileX < mapSizeX && tileY >= 0 && tileY < mapSizeY &&
		buildingsMap[tileX][tileY] != nullptr);
}

inline bool BuildingsMap::isVoidBuilding(const int tileX, const int tileY)
{
	return (tileX >= 0 && tileX < mapSizeX && tileY >= 0 && tileY < mapSizeY &&
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

bool BuildingsMap::getIsMapChanged() { return isMapChanged; }
void BuildingsMap::cleanMapChanged() { isMapChanged = false; }


void BuildingsMap::intetractMap()
{
	for (int x = 0; x < mapSizeX; ++x)
	{
		for (int y = 0; y < mapSizeY; ++y)
		{
			if (buildingsMap[x][y] != nullptr && buildingsMap[x][y]->getType() != AUXILARY)
			{
				buildingsMap[x][y]->interact();
			}
		}
	}
}


void BuildingsMap::addToInventory(const int resType, const TileCoord tile)
{
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	buildingsMap[mainTile.x][mainTile.y]->addToInventory(resType, 1);
}


bool BuildingsMap::isThisPositionFree(const TileCoord tile, const int position)
{
	if (!buildingExists(tile))
		return false;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->isThisPositionFree(position);
}

void BuildingsMap::leavePosition(const TileCoord tile, const int position)
{
	buildingsMap[tile.x][tile.y]->leavePosition(position);
}

void BuildingsMap::takePosition(const TileCoord tile, const int position)
{
	buildingsMap[tile.x][tile.y]->takePosition(position);
}

bool BuildingsMap::canAccept(const int resType, const TileCoord tile)
{
	if (!buildingExists(tile))
		return false;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->canAccept(resType);
}


int BuildingsMap::getBuildingType(const TileCoord tile)
{
	if (!buildingExists(tile))
		return VOID_;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->getType();
}


void BuildingsMap::setTurret(const int turretType, const TileCoord tile)
{
	if (!buildingExists(tile) ||
		(buildingsMap[tile.x][tile.y]->getType() != STONE_TOWER && buildingsMap[tile.x][tile.y]->getType() != STEEL_TOWER))
	{
		return;
	}

	if (t1::res::isEnoughAllRes(g_BuildingsInfoArray[turretType].costToBuild))
	{
		t1::res::wasteRes(g_BuildingsInfoArray[turretType].costToBuild);
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
