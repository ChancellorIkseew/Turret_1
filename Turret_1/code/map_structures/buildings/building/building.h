#pragma once
#ifndef BUILDING_H
#define BUILDING_H

#include <list>
#include <SFML/Graphics.hpp>
#include <cereal/archives/binary.hpp>

#include "map_structures/base_engine/base_engine.h"
#include "map_structures/resources/resource_unit.h"
#include "map_structures/buildings/building/buildings_enum.h"

class Team;
class Core;
class BuildingsMap;
class World;

struct StoredResource
{
	uint16_t type = 0;
	uint16_t quantity = 0;
};

class Building
{
private:
	static inline World* world;
	std::list<StoredResource> inventory;
	Team* team = nullptr;
protected:
	TileCoord tile = TileCoord(0, 0);
private:
	uint16_t type = 0;
	int16_t durability = 0;
	uint8_t size = 0;

	inline void placeResourceUnit(const uint16_t resType, const TileCoord tile, BuildingsMap& buildingsMap);

protected:
	char direction;

	static inline sf::Image buildingsImage;
	static inline sf::Texture buildingsTexture;
	static inline sf::Sprite buildingSprite;

	void placeResourceUnitX1(const uint16_t resType, BuildingsMap& buildingsMap);
	void placeResourceUnitX4(const uint16_t resType, BuildingsMap& buildingsMap);
	void placeResourceUnitX9(const uint16_t resType, BuildingsMap& buildingsMap);
	bool isStorageFull(const short capacity) const;

public:
	Building(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	Building() = default;
	virtual ~Building() = default;

	virtual void save(cereal::BinaryOutputArchive& archive) const;
	virtual void load(cereal::BinaryInputArchive& archive);

	static std::shared_ptr<Building> createBuilding(const BuildingType type, const char direction, const TileCoord tile, Team* const team);

	virtual void interact();
	void setDamage(const int16_t damage);
	void setDamage(const float damage);
	void setDurability(const int16_t durability);
	TileCoord getTileCoord() const { return tile; }
	uint8_t getSize() const { return size; }
	int16_t getDurability() const { return durability; }
	char getDirection() const { return direction; }
	std::list<StoredResource>& getInventory() { return inventory; }
	Team* getTeam() const { return team; }
	int getTeamID() const;

	virtual BuildingType getType() const = 0;

	// resouses_and_inventory
	virtual bool canAccept(const uint16_t resType) const;
	virtual bool canAccept(const ResourceUnit& unit) const;

	int findResource() const;
	bool isEnoughRes(const uint16_t resType, const uint16_t amount) const;
	void wasteResorce(const uint16_t resType, const uint16_t amount);
	void addToInventory(const uint16_t resType, const uint16_t amount);
	virtual void addToInventory(ResourceUnit& unit);

	// resUnits_and_inventory
	bool hasCorrectConveyerUp(const TileCoord tile, const BuildingsMap& buildingsMap) const;
	bool hasCorrectConveyerLeft(const TileCoord tile, const BuildingsMap& buildingsMap) const;
	bool hasCorrectConveyerDown(const TileCoord tile, const BuildingsMap& buildingsMap) const;
	bool hasCorrectConveyerRight(const TileCoord tile, const BuildingsMap& buildingsMap) const;

	// turrets
	virtual void setTurret(const BuildingType turretType);
	virtual void removeTurret();
	virtual bool isTurretOnTower() const;

	// visual
	static void prepareSprites();
	virtual void animation();
	virtual void draw(sf::RenderWindow& window) = 0;

	static void initWorld(World* world) {
		Building::world = world;
	}
	friend Core;

};

#endif // BUILDING_H
