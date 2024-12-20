
#include <iostream>

#include "buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/buildings/building/buildings_info.h"

#include "game_interface/gameplay/gameplay_util/camera.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/base_engine/base_engine.h"
#include "map_structures/team/team.h"

#include "t1_system/events/events_handler.h"


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
	std::cout << "suc�essfull_buildings_map_load" << '\n';
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
		buildingsMap[iTileX][iTileY] = Building::createBuilding(AUXILARY, 0, tile, team);
	}
}


void BuildingsMap::constructBuilding(const uint16_t type, const char direction, const TileCoord tile, Team* const team)
{
	if (t1::bc::buildingsInfoTable.find(type) == t1::bc::buildingsInfoTable.end())
		return;

	if (team->getBalance().isEnough(t1::bc::buildingsInfoTable[type].costToBuild))
	{
		if (placeBuilding(type, direction, tile, team))
			team->getBalance().waste(t1::bc::buildingsInfoTable[type].costToBuild);
	}
}


bool BuildingsMap::placeBuilding(const uint16_t type, const char direction, const TileCoord tile, Team* const team)
{
	if (!isAvaluablePlaceBuilding(type, tile, team))
		return false;
	auto building = Building::createBuilding(type, direction, tile, team);
	buildingsMap[tile.x][tile.y] = building;
	int size = t1::bc::buildingsInfoTable[type].size;
	createAuxilary(size, tile, team);
	if (type == CORE_MK1 || type == CORE_MK2 || type == CORE_MK3)
		cores.emplace_back(building);
	justTriggeredTiles.push_back(tile);
	return true;
}


bool BuildingsMap::isAvaluablePlaceBuilding(const uint16_t type, const TileCoord tile, Team* const team)
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
	uint16_t type = buildingsMap[mainBuilding.x][mainBuilding.y]->getType();
	short size = buildingsMap[mainBuilding.x][mainBuilding.y]->getSize();
	for (int i = 0; i < size; ++i)
	{
		TileCoord iTile = mainBuilding + t1::be::coordSquareArr[i];
		buildingsMap[iTile.x][iTile.y].reset();
		justTriggeredTiles.push_back(iTile);
	}
	if (type == CORE_MK1 || type == CORE_MK2 || type == CORE_MK3)
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

std::list<StoredResource> BuildingsMap::getInventory(const TileCoord tile)
{
	if (!buildingExists(tile))
	{
		std::list<StoredResource> nullInventory;
		return nullInventory;
	}
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->getInventory();
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

void BuildingsMap::pushChanges()
{
	if (justTriggeredTiles.empty())
		return;
	EventsHandler::pushEvent(t1::EventType::MAP_CHANGED, std::make_unique<t1::MapChanged>(justTriggeredTiles));
	justTriggeredTiles.clear();
}

const std::vector<std::shared_ptr<Building>>& BuildingsMap::getCores()
{
	return cores;
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


void BuildingsMap::setTurret(const uint16_t turretType, const TileCoord tile, Team* const team)
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
	const TileCoord start = Camera::getStartTile();
	const TileCoord end = Camera::getEndTile();

	for (int x = start.x; x < end.x; ++x)
	{
		for (int y = start.y; y < end.y; ++y)
		{
			if (buildingsMap[x][y] != nullptr && buildingsMap[x][y]->getType() != AUXILARY)
			{
				buildingsMap[x][y]->draw(window);
			}
		}
	}
}
