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
	static inline std::vector<std::vector<std::shared_ptr<Building>>> buildingsMap;
	
	static void createAuxilary(const short size, const TileCoord tile);

public:
		
	BuildingsMap(std::string saveFolderName);
	~BuildingsMap() = default;
		
	static void generateMap();
	static void loadMap();
	static void saveMap();
		
	static void intetractMap();

	// Construction_process
	static void constructBuilding(const int type, const char direction, const TileCoord tile);
	static void demolishBuilding(const TileCoord tile);
		
	// Simple_utilites
	static bool buildingExists(const TileCoord tile);
	static void setBuildingDurability(const short durability, const TileCoord tile);
	static void setDamage(const short damage, const TileCoord tile);
	static int getBuildingType(const TileCoord tile);
	static short getBuildingDurability(const TileCoord tile);
	static TileCoord getBuildingMainTileCoord(const TileCoord tile);

	static bool getIsMapChanged();
	static void cleanMapChanged();
	
	// resources_and_inventory
	static bool canAccept(const int resType, const TileCoord tile);
	static bool isThisPositionFree(const TileCoord tile, const int position);
	static void leavePosition(const TileCoord tile, const int position);
	static void takePosition(const TileCoord tile, const int position);
	static void addToInventory(const int resType, const TileCoord tile);

	// turrets
	static void setTurret(const int turretType, const TileCoord tile);
	static void removeTurret(const TileCoord tile);
	static bool isTurretOnTile(const TileCoord tile);
		
	// Visual
	static void drawMap(sf::RenderWindow& window);
		
};


#endif // BUILDINGS_MAP_H
