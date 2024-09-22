
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>


#include "buildings_map.h"
#include "building/buildings_enum.h"
#include "building/buildings_info.h"

#include "map_structures/pre-settings/pre-settings.h"

#include "game_interface/gameplay/gameplay_util/camera.h"

#include "map_structures/base_engine/tile_coord.h"
#include "map_structures/resources/resources.h"


#include "building/building_types/walls/stone_wall.h"
#include "building/building_types/walls/tower_types/stone_tower.h"
#include "building/building_types/drills/drill.h"
#include "building/building_types/drills/drill_types/small_drill.h"
#include "building/building_types/drills/drill_types/big_drill.h"
#include "building/building_types/logistics/conveer.h"
#include "building/building_types/logistics/conveer_types/shielded_conveer.h"
#include "building/building_types/logistics/bridge/bridge.h"
#include "building/building_types/logistics/router/router.h"
#include "building/building_types/storages/core.h"
#include "building/building_types/factories/factory_types/shell_factory.h"
#include "building/building_types/factories/factory_types/rocket_factory.h"


BuildingsMap::BuildingsMap(std::string saveFolderName)
{
	mapMaxX = PreSettings::getMapMaxX();
	mapMaxY = PreSettings::getMapMaxY();

	buildingsArr = new Building** [mapMaxX];
	for (int x = 0; x < mapMaxX; ++x)
	{
		buildingsArr[x] = new Building* [mapMaxY];
	}

	saveFileName = "saves/" + saveFolderName + "/buildings.txt";
	isMapChanged = false;
}



void BuildingsMap::generateMap()
{
	
	for(int y=0; y < mapMaxY; y++)
	{
		for(int x=0; x < mapMaxX; x++)
		{
			buildingsArr[x][y] = new Building(bType::VOID_, 0, 1, x, y);
		}
	}

	delete buildingsArr[48][48];
	buildingsArr[48][48] = setBuilding(CORE_MK1, '0', 900, 16, 48, 48);
	
	for (int i = 1; i < 16; i++)
	{
		buildingsArr[48 + coordSquareArr[i].x][48 + coordSquareArr[i].y]->type = AUXILARY;
		buildingsArr[48 + coordSquareArr[i].x][48 + coordSquareArr[i].y]->size = 16;
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
				if (bType == VOID_ || bType == AUXILARY)
				{
					buildingsArr[x][y] = new Building(bType, 0, 1, x, y);
				}
				else
				{
					buildingsArr[x][y] = createBuilding(bType);
				}
				buildingsArr[x][y]->load(fin);
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
				buildingsArr[x][y]->save(fout);
			}
		}
	}
	fout.close();
	std::cout << "Save_buildings_map_works" <<'\n';
}



void BuildingsMap::Print()
{
	
	for(int y=0; y<mapMaxY; y++)
	{
		for(int x=0; x<mapMaxX; x++)
		{
			std::cout<< buildingsArr[x][y]->type;
			
		}
	
		std::cout<<'\n';
	}
	std::cout<< "array end" <<'\n';
}



void BuildingsMap::constructBuilding(int buildingType, char direction, int tileX, int tileY)
{
	int size = g_BuildingsInfoArray[buildingType].size;
	int durability = g_BuildingsInfoArray[buildingType].durability * PreSettings::getBuildingsMaxDurabilityModidier();

	for (int i = 0; i < size; i++)
	{
		if (tileX + coordSquareArr[i].x < 0 || tileX + coordSquareArr[i].x >= mapMaxX || 
			tileY + coordSquareArr[i].y < 0 || tileY + coordSquareArr[i].y >= mapMaxY)
		{
			return;
		}

		if (buildingsArr[tileX + coordSquareArr[i].x][tileY + coordSquareArr[i].y]->type != VOID_)
		{
			return;
		}
	}	// cheeck_square_for_building

	if (isEnoughAllRes(g_BuildingsInfoArray[buildingType].costToBuild))
	{
		wasteRes(g_BuildingsInfoArray[buildingType].costToBuild);

		delete buildingsArr[tileX][tileY];
		buildingsArr[tileX][tileY] = setBuilding(buildingType, direction, durability, size, tileX, tileY);

		if (size > 1)
		{
			for (int i = 1; i < size; i++)
			{
				buildingsArr[tileX + coordSquareArr[i].x][tileY + coordSquareArr[i].y]->type = AUXILARY;
				buildingsArr[tileX + coordSquareArr[i].x][tileY + coordSquareArr[i].y]->size = size;
			}
		}

	

		isMapChanged = true;
	}

}



void BuildingsMap::demolishBuilding(int tileX, int tileY)
{
	if (buildingsArr[tileX][tileY]->type != bType::AUXILARY)
	{
		if (buildingsArr[tileX][tileY]->size != 1)
		{
			for (int i = 1; i < buildingsArr[tileX][tileY]->size; i++)
			{
				buildingsArr[tileX + coordSquareArr[i].x][tileY + coordSquareArr[i].y]->type = bType::VOID_;
				buildingsArr[tileX + coordSquareArr[i].x][tileY + coordSquareArr[i].y]->size = 1;
			}
		}

		delete buildingsArr[tileX][tileY];
		buildingsArr[tileX][tileY] = new Building(VOID_, 0, 1, tileX, tileY);

		isMapChanged = true;
	}
	else
	{
		TileCoord mainBuilding = getBuildingMainTileCoord(tileX, tileY);
		demolishBuilding(mainBuilding.x, mainBuilding.y);
	}
}



void BuildingsMap::setDamage(short damage, int tileX, int tileY)
{
	if (tileX < 0 || tileX >= mapMaxX || tileY < 0 || tileY >= mapMaxY)
	{
		return;
	}

	if (buildingsArr[tileX][tileY]->type != VOID_)
	{
		if (buildingsArr[tileX][tileY]->type != AUXILARY)
		{
			buildingsArr[tileX][tileY]->durability = buildingsArr[tileX][tileY]->durability - damage;

			if (buildingsArr[tileX][tileY]->durability < 1)
			{
				demolishBuilding(tileX, tileY);
			}
		}
		else
		{
			TileCoord mainBuilding = getBuildingMainTileCoord(tileX, tileY);
			setDamage(damage ,mainBuilding.x, mainBuilding.y);
		}
		
	}
}




TileCoord BuildingsMap::getBuildingMainTileCoord(int tileX, int tileY)
{
	for (int i = 0; i < buildingsArr[tileX][tileY]->size; ++i)
	{
		if (buildingsArr[tileX - coordSquareArr[i].x][tileY - coordSquareArr[i].y]->size == buildingsArr[tileX][tileY]->size &&
			buildingsArr[tileX - coordSquareArr[i].x][tileY - coordSquareArr[i].y]->type != AUXILARY)
		{
			return { tileX - coordSquareArr[i].x , tileY - coordSquareArr[i].y };
		}
	}
	return {0,0};
}



void BuildingsMap::setBuildingDurability(short durability, int tileX, int tileY)
{
	buildingsArr[tileX][tileY]->durability = durability;
}



void BuildingsMap::setBuildingType(char type, int tileX, int tileY)
{
	buildingsArr[tileX][tileY]->type = type;
}



char BuildingsMap::getBuildingType(int tileX, int tileY) 
{
	if (tileX < 0 || tileX >= mapMaxX || tileY < 0 || tileY >= mapMaxY)
	{
		return VOID_;
	}
	return buildingsArr[tileX][tileY]->type; 
}

short BuildingsMap::getBuildingDurability(int tileX, int tileY) 
{ 
	if (tileX < 0 || tileX >= mapMaxX || tileY < 0 || tileY >= mapMaxY)
	{
		return VOID_;
	}
	return buildingsArr[tileX][tileY]->durability; 
}

bool BuildingsMap::getIsMapChanged() { return isMapChanged; }

void BuildingsMap::cleanMapChanged() { isMapChanged = false; }





BuildingsMap::~BuildingsMap()
{
	for (int x = 0; x < mapMaxX; ++x) 
	{
		for (int y = 0; y < mapMaxY; ++y) 
		{
			if (buildingsArr[x][y] != nullptr) 
			{
				delete buildingsArr[x][y];
				buildingsArr[x][y] = nullptr;
			}
		}
		delete[] buildingsArr[x];
		buildingsArr[x] = nullptr;
	}
	delete[] buildingsArr;
	buildingsArr = nullptr;
}



Building* BuildingsMap::setBuilding(int type, char direction,  short durability, short size, int tileX, int tileY)
{
	switch (type)
	{
	case CORE_MK1:
		return new Core(CORE_MK1, durability, size, tileX, tileY);

	case STONE_WALL:
		return new StoneWall(STONE_WALL, durability, size, tileX, tileY);

	case STONE_TOWER:
		return new StoneTower(STONE_TOWER, durability, size, tileX, tileY);

	case STANDARD_CONVEYER_UP:
		return new Conveyer(STANDARD_CONVEYER_UP, 'w', durability, size, tileX, tileY);
	case STANDARD_CONVEYER_LEFT:
		return  new Conveyer(STANDARD_CONVEYER_LEFT, 'a', durability, size, tileX, tileY);	
	case STANDARD_CONVEYER_DOWN:
		return new Conveyer(STANDARD_CONVEYER_DOWN, 's', durability, size, tileX, tileY);
	case STANDARD_CONVEYER_RIGHT:
		return new Conveyer(STANDARD_CONVEYER_RIGHT, 'd', durability, size, tileX, tileY);

	case SHIELDED_CONVEYER_UP:
		return new ShieldedConveyer(SHIELDED_CONVEYER_UP, 'w', durability, size, tileX, tileY);
	case SHIELDED_CONVEYER_LEFT:
		return  new ShieldedConveyer(SHIELDED_CONVEYER_LEFT, 'a', durability, size, tileX, tileY);
	case SHIELDED_CONVEYER_DOWN:
		return new ShieldedConveyer(SHIELDED_CONVEYER_DOWN, 's', durability, size, tileX, tileY);
	case SHIELDED_CONVEYER_RIGHT:
		return new ShieldedConveyer(SHIELDED_CONVEYER_RIGHT, 'd', durability, size, tileX, tileY);

	case BRIDGE:
		return new Bridge(BRIDGE, direction, durability, size, tileX, tileY);

	case ROUTER:
		return new Router(ROUTER, durability, size, tileX, tileY);

	case SMALL_DRILL:
		return new SmallDrill(SMALL_DRILL, durability, size, tileX, tileY);

	case BIG_DRILL:
		return new BigDrill(BIG_DRILL, durability, size, tileX, tileY);

	case EFFECTIVE_DRILL:
		break;

	case REINFORCED_DRILL:
		break;

	case SHELL_FACTORY:
		return new ShellFactory(SHELL_FACTORY, durability, size, tileX, tileY);

	case ROCKET_FACTORY:
		return new RocketFactory(ROCKET_FACTORY, durability, size, tileX, tileY);

	default:
		return nullptr;
	}
}



Building* BuildingsMap::createBuilding(int type)
{
	switch (type)
	{
	case CORE_MK1:
		return new Core;

	case STONE_WALL:
		return new StoneWall;

	case STONE_TOWER:
		return new StoneTower;

	case STANDARD_CONVEYER:
	case STANDARD_CONVEYER_UP:
	case STANDARD_CONVEYER_LEFT:
	case STANDARD_CONVEYER_DOWN:
	case STANDARD_CONVEYER_RIGHT:
		return new Conveyer;

	case SHIELDED_CONVEYER:
	case SHIELDED_CONVEYER_UP:
	case SHIELDED_CONVEYER_LEFT:
	case SHIELDED_CONVEYER_DOWN:
	case SHIELDED_CONVEYER_RIGHT:
		return new ShieldedConveyer;

	case BRIDGE:
		return new Bridge;

	case ROUTER:
		return new Router;

	//case SORTER:
		//return new SORTER;

	case SMALL_DRILL:
		return new SmallDrill;

	case BIG_DRILL:
		return new BigDrill;
#ifdef A
	case EFFECTIVE_DRILL:
		return new EffectiveDrill;

	case REINFORCED_DRILL:
		return new ReinforcedDrill;
#endif // A
	case SHELL_FACTORY:
		return new ShellFactory;

	case ROCKET_FACTORY:
		return new RocketFactory;

	default:
		return nullptr;
	}
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
			if (buildingsArr[x][y]->type != VOID_ && buildingsArr[x][y]->type != AUXILARY)
			{
				buildingsArr[x][y]->draw(window);
			}
		}
	}
}



void BuildingsMap::intetractMap()
{
	for (int y = 0; y < mapMaxY; ++y)
	{
		for (int x = 0; x < mapMaxX; ++x)
		{
			if (buildingsArr[x][y]->type != VOID_ && buildingsArr[x][y]->type != AUXILARY)
			{
				buildingsArr[x][y]->interact();
			}
		}
	}
}



void BuildingsMap::addToInventory(int resType, int tileX, int tileY)
{
	TileCoord mainTile = getBuildingMainTileCoord(tileX, tileY);

	buildingsArr[mainTile.x][mainTile.y]->addToInventory(resType, 1);
}



bool BuildingsMap::isThisPositionFree(int tileX, int tileY, int position)
{
	if (buildingsArr[tileX][tileY]->type != AUXILARY)
	{
		return buildingsArr[tileX][tileY]->isThisPositionFree(position);
	}
	else
	{
		TileCoord mainTile = getBuildingMainTileCoord(tileX, tileY);

		return buildingsArr[mainTile.x][mainTile.y]->isThisPositionFree(position);
	}
}

void BuildingsMap::leavePosition(int tileX, int tileY, int position)
{
	buildingsArr[tileX][tileY]->leavePosition(position);
}

void BuildingsMap::takePosition(int tileX, int tileY, int position)
{
	buildingsArr[tileX][tileY]->takePosition(position);
}

bool BuildingsMap::canAccept(int resType, int tileX, int tileY)
{
	if (tileX < 0 || tileX > mapMaxX || tileY < 0 || tileY > mapMaxY)
	{
		return false;
	}

	if (buildingsArr[tileX][tileY]->type != AUXILARY)
	{
		return buildingsArr[tileX][tileY]->canAccept(resType);
	}
	else
	{
		TileCoord mainTile = getBuildingMainTileCoord(tileX, tileY);

		return buildingsArr[mainTile.x][mainTile.y]->canAccept(resType);
	}
}




int BuildingsMap::getBuildingMainTileType(int tileX, int tileY)
{
	for (int i = 1; i < buildingsArr[tileX][tileY]->size; ++i)
	{
		if (buildingsArr[tileX - coordSquareArr[i].x][tileY - coordSquareArr[i].y]->size == buildingsArr[tileX][tileY]->size &&
			buildingsArr[tileX - coordSquareArr[i].x][tileY - coordSquareArr[i].y]->type != AUXILARY)
		{
			return buildingsArr[tileX - coordSquareArr[i].x][tileY - coordSquareArr[i].y]->type;
		}
	}

	return VOID_;
}



void BuildingsMap::setTurret(int turretType, int tileX, int tileY)
{
	if (buildingsArr[tileX][tileY]->type != STONE_TOWER &&
		buildingsArr[tileX][tileY]->type != STEEL_TOWER)
	{
		return;
	}

	if (isEnoughAllRes(g_BuildingsInfoArray[turretType].costToBuild))
	{
		wasteRes(g_BuildingsInfoArray[turretType].costToBuild);
		buildingsArr[tileX][tileY]->setTurret(turretType);
	}
}

void BuildingsMap::removeTurret(int tileX, int tileY)
{
	buildingsArr[tileX][tileY]->removeTurret();
}

bool BuildingsMap::isTurretOnTile(int tileX, int tileY)
{
	return buildingsArr[tileX][tileY]->isTurretOnTower();
}
