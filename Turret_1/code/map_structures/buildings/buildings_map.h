#pragma once
#ifndef BUILDINGS_MAP_H
#define BUILDINGS_MAP_H

#include <string>
#include <SFML\Graphics.hpp>

#include "../base_engine/tile_coord.h"
#include "building/building.h"


class BuildingsMap
{
private:

	static inline int mapMaxX, mapMaxY;
	
	static inline std::string saveFileName;
	
	static inline Building*** buildingsArr;	// Building_inventory

	static inline bool isMapChanged;
	
public:
		
	BuildingsMap(std::string saveFolderName);
	~BuildingsMap();
		
	static void generateMap();
	static void loadMap();
	static void saveMap();
		
	static void intetractMap();

	// Construction_process
	static void constructBuilding(int buildingType, char direction, int tileX, int tileY);
	static void demolishBuilding(int tileX, int tileY);

	static Building* setBuilding(int type, char direction, short durability, short v_size, int tileX, int tileY);
	static Building* createBuilding(int type);
		
	// Simple_utilites
	static void setBuildingType(char v_type, int tileX, int tileY);
	static void setBuildingDurability(short durability, int tileX, int tileY);
	static void setDamage(short damage, int tileX, int tileY);
	static char getBuildingType(int tileX, int tileY);
	static short getBuildingDurability(int tileX, int tileY);
	static TileCoord getBuildingMainTileCoord(int x, int y);
	static int getBuildingMainTileType(int tileX, int tileY);
	static void Print();

	static bool getIsMapChanged();
	static void cleanMapChanged();
	
	// resources_and_inventory
	static bool canAccept(int resType, int tileX, int tileY);
	static bool isThisPositionFree(int tileX, int tileY, int position);
	static void leavePosition(int tileX, int tileY, int position);
	static void takePosition(int tileX, int tileY, int position);
	static void addToInventory(int resType, int tileX, int tileY);

	// turrets
	static void setTurret(int turretType, int tileX, int tileY);
	static void removeTurret(int tileX, int tileY);
	static bool isTurretOnTile(int tileX, int tileY);
		
	// Visual
	static void drawMap(sf::RenderWindow& window);
		
};


#endif // BUILDINGS_MAP_H