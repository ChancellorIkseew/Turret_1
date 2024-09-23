#pragma once
#ifndef BUILDINGS_MAP_H
#define BUILDINGS_MAP_H

#include <string>
#include <vector>
#include <SFML\Graphics.hpp>

#include "map_structures/base_engine/tile_coord.h"
#include "building/building.h"


class BuildingsMap
{
private:

	static inline int mapMaxX, mapMaxY;
	static inline bool isMapChanged;

	static inline std::string saveFileName;
	static inline std::vector<std::vector<Building*>> buildingsMap;
	
public:
		
	BuildingsMap(std::string saveFolderName);
	~BuildingsMap();
		
	static void generateMap();
	static void loadMap();
	static void saveMap();
		
	static void intetractMap();

	// Construction_process
	static void constructBuilding(const int type, const char direction, const int tileX, const int tileY);
	static void demolishBuilding(const int tileX, const int tileY);
		
	// Simple_utilites
	static bool buildingExists(const int tileX, const int tileY);
	static void setBuildingDurability(const short durability, const int tileX, const int tileY);
	static void setDamage(const short damage, const int tileX, const int tileY);
	static int getBuildingType(const int tileX, const int tileY);
	static short getBuildingDurability(const int tileX, const int tileY);
	static TileCoord getBuildingMainTileCoord(const int tileX, const int tileY);
	//static int getBuildingMainTileType(const int tileX, const int tileY);

	static bool getIsMapChanged();
	static void cleanMapChanged();
	
	// resources_and_inventory
	static bool canAccept(const int resType, const int tileX, const int tileY);
	static bool isThisPositionFree(const int tileX, const int tileY, const int position);
	static void leavePosition(const int tileX, const int tileY, const int position);
	static void takePosition(const int tileX, const int tileY, const int position);
	static void addToInventory(const int resType, const int tileX, const int tileY);

	// turrets
	static void setTurret(const int turretType, const int tileX, const int tileY);
	static void removeTurret(const int tileX, const int tileY);
	static bool isTurretOnTile(const int tileX, const int tileY);
		
	// Visual
	static void drawMap(sf::RenderWindow& window);
		
};


#endif // BUILDINGS_MAP_H
