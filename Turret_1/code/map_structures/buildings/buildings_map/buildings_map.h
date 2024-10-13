#pragma once
#ifndef BUILDINGS_MAP_H
#define BUILDINGS_MAP_H

#include <string>
#include <vector>
#include <SFML\Graphics.hpp>

#include "map_structures/base_engine/tile_coord.h"
#include "map_structures/buildings/building/building.h"


class BuildingsMap
{
private:
	static inline int mapSizeX, mapSizeY;
	static inline bool isMapChanged;
	static inline std::vector<std::vector<std::shared_ptr<Building>>> buildingsMap;
	
	static void createAuxilary(const short size, const TileCoord tile, Team* team);

public:
	BuildingsMap(const TileCoord mapSize);
	~BuildingsMap();
	
	static void loadMap(const std::string& folder);
	static void saveMap(const std::string& folder);
	
	static void intetractMap();

	// Construction_process
	static void constructBuilding(const int type, const char direction, const TileCoord tile, Team* team);
	static void demolishBuilding(const TileCoord tile);
	
	// Simple_utilites
	static inline bool buildingExists(const int tileX, const int tileY);
	static inline bool isVoidBuilding(const int tileX, const int tileY);
	static bool buildingExists(const TileCoord tile);
	static bool isVoidBuilding(const TileCoord tile);
	static void setBuildingDurability(const short durability, const TileCoord tile);
	static void setDamage(const short damage, const TileCoord tile);
	static int getBuildingType(const TileCoord tile);
	static short getBuildingDurability(const TileCoord tile);
	static char getBuildingDirection(const TileCoord tile);
	static TileCoord getBuildingMainTileCoord(const TileCoord tile);
	static Team* getTeam(const TileCoord tile);
	static int getTeamID(const TileCoord tile);

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
