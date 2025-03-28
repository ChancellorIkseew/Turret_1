#pragma once
#ifndef BUILDINGS_MAP_H
#define BUILDINGS_MAP_H

#include <vector>
#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>

#include "map_structures/base_engine/base_engine.h"

enum class BuildingType : uint16_t;
enum class ResType : uint8_t;

class Team;
class Camera;
class Building;
class ResourceUnit;
struct StoredResource;

class BuildingsMap
{
private:
	TileCoord mapSize;
	std::vector<std::vector<std::shared_ptr<Building>>> buildingsMap;
	std::vector<std::shared_ptr<Building>> cores;
	std::vector<TileCoord> justChangedTiles;
	
	void createAuxilary(const uint8_t size, const TileCoord mainTile, Team* team);

public:
	BuildingsMap(const TileCoord mapSize);
	BuildingsMap() = default;
	~BuildingsMap() = default;
	
	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);
	
	void intetract();
	void pushChanges();
	const std::vector<std::shared_ptr<Building>>& getCores() const;

	// Construction_process
	void constructBuilding(const BuildingType type, const char direction, const TileCoord tile, Team* team);
	bool placeBuilding(const BuildingType type, const char direction, const TileCoord tile, Team* team);
	bool isAvaluablePlaceBuilding(const BuildingType type, const TileCoord tile, Team* team) const;
	void demolishBuilding(const TileCoord tile);
	
	// Simple_utilites
	inline bool buildingExists(const int tileX, const int tileY) const;
	inline bool isVoidBuilding(const int tileX, const int tileY) const;
	bool buildingExists(const TileCoord tile) const;
	bool isVoidBuilding(const TileCoord tile) const;

	// Get_set
	BuildingType getBuildingType(const TileCoord tile) const;
	short getBuildingDurability(const TileCoord tile) const;
	char getBuildingDirection(const TileCoord tile) const;
	TileCoord getBuildingMainTileCoord(const TileCoord tile) const;
	std::list<StoredResource> getInventory(const TileCoord tile) const;
	Team* getTeam(const TileCoord tile) const;
	int getTeamID(const TileCoord tile) const;
	void setBuildingDurability(const int16_t durability, const TileCoord tile);
	void setDamage(const int16_t damage, const TileCoord tile);
	void setDamage(const float damage, const TileCoord tile);

	// resources_and_inventory
	bool canAccept(const ResType resType, const TileCoord tile) const;
	bool canAccept(const ResourceUnit& unit, const TileCoord tile) const;
	void addToInventory(const ResType resType, const TileCoord tile);
	void addToInventory(ResourceUnit& unit, const TileCoord tile);
	
	// Visual
	void draw(sf::RenderWindow& window, const Camera& camera);

};


#endif // BUILDINGS_MAP_H
