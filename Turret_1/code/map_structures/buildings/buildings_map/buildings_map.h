#pragma once
#ifndef BUILDINGS_MAP_H
#define BUILDINGS_MAP_H

#include <vector>
#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>

#include "map_structures/base_engine/base_engine.h"
#include "map_structures/buildings/building/building.h"
#include "map_structures/resources/resource_unit.h"


class BuildingsMap
{
private:
	TileCoord mapSize = TileCoord(0, 0);
	std::vector<std::vector<std::shared_ptr<Building>>> buildingsMap;
	std::vector<std::shared_ptr<Building>> cores;
	std::vector<TileCoord> justChangedTiles;
	
	void createAuxilary(const short size, const TileCoord tile, Team* team);

public:
	BuildingsMap(const TileCoord mapSize);
	BuildingsMap() = default;
	~BuildingsMap() = default;
	
	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);
	
	void intetractMap();
	void pushChanges();
	const std::vector<std::shared_ptr<Building>>& getCores() const;

	// Construction_process
	void constructBuilding(const uint16_t type, const char direction, const TileCoord tile, Team* const team);
	bool placeBuilding(const uint16_t type, const char direction, const TileCoord tile, Team* const team);
	bool isAvaluablePlaceBuilding(const uint16_t type, const TileCoord tile, Team* const team) const;
	void demolishBuilding(const TileCoord tile);
	
	// Simple_utilites
	inline bool buildingExists(const int tileX, const int tileY) const;
	inline bool isVoidBuilding(const int tileX, const int tileY) const;
	bool buildingExists(const TileCoord tile) const;
	bool isVoidBuilding(const TileCoord tile) const;
	int getBuildingType(const TileCoord tile) const;
	short getBuildingDurability(const TileCoord tile) const;
	char getBuildingDirection(const TileCoord tile) const;
	TileCoord getBuildingMainTileCoord(const TileCoord tile) const;
	std::list<StoredResource> getInventory(const TileCoord tile) const;
	Team* getTeam(const TileCoord tile) const;
	int getTeamID(const TileCoord tile) const;
	void setBuildingDurability(const short durability, const TileCoord tile);
	void setDamage(const short damage, const TileCoord tile);

	// resources_and_inventory
	bool canAccept(const uint16_t resType, const TileCoord tile) const;
	bool canAccept(const ResourceUnit& unit, const TileCoord tile) const;
	void addToInventory(const uint16_t resType, const TileCoord tile);
	void addToInventory(ResourceUnit& unit, const TileCoord tile);

	// turrets
	void setTurret(const uint16_t turretType, const TileCoord tile, Team* const team);
	void removeTurret(const TileCoord tile);
	bool isTurretOnTile(const TileCoord tile) const;
	
	// Visual
	void draw(sf::RenderWindow& window);

};


#endif // BUILDINGS_MAP_H
;