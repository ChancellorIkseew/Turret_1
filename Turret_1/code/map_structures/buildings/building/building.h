#pragma once
#ifndef BUILDING_H
#define BUILDING_H

#include <list>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "map_structures/base_engine/tile_coord.h"
#include "map_structures/resources/resource_unit.h"

class Team;
class Core;

struct StoredResource
{
	uint16_t type;
	uint16_t quantity;
};

class Building
{
private:
	std::list<StoredResource> storedResourcesList;
	Team* team;
protected:
	TileCoord tile;
private:
	uint16_t type;
	int16_t durability;
	uint8_t size;

	inline void placeResourceUnit(const uint16_t resType, const TileCoord tile);

protected:
	char direction;

	static inline sf::Image buildingsImage;
	static inline sf::Texture buildingsTexture;
	static inline sf::Sprite buildingSprite;

	void placeResourceUnitX1(const uint16_t resType);
	void placeResourceUnitX4(const uint16_t resType);
	void placeResourceUnitX9(const uint16_t resType);
	bool isStorageFull(const short capacity) const;

public:
	Building(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	virtual ~Building() = default;

	virtual void save(std::ofstream& fout) const;
	virtual void load(std::ifstream& fin);

	static std::shared_ptr<Building> createBuilding(const uint16_t type, const char direction, const TileCoord tile, Team* const team);

	virtual void interact();
	void setDamage(const int damage);
	void setDurability(const int durability);
	TileCoord getTileCoord() const;
	int getType() const;
	short getDurability() const;
	short getSize() const;
	char getDirection() const;
	Team* getTeam() const;
	int getTeamID() const;

	// resouses_and_inventory
	virtual bool canAccept(const uint16_t resType) const;
	virtual bool canAccept(const ResourceUnit& unit) const;

	int findResource() const;
	bool isEnoughRes(const uint16_t resType, const uint16_t amount) const;
	void wasteResorce(const uint16_t resType, const uint16_t amount);
	void addToInventory(const uint16_t resType, const uint16_t amount);
	virtual void addToInventory(ResourceUnit& unit);

	// resUnits_and_inventory
	bool hasCorrectConveyerUp(const TileCoord tile) const;
	bool hasCorrectConveyerLeft(const TileCoord tile) const;
	bool hasCorrectConveyerDown(const TileCoord tile) const;
	bool hasCorrectConveyerRight(const TileCoord tile) const;

	// turrets
	virtual void setTurret(const uint16_t turretType);
	virtual void removeTurret();
	virtual bool isTurretOnTower() const;

	// visual
	static void prepareSprites();
	virtual void animation();
	virtual void draw(sf::RenderWindow& window) = 0;

	friend Core;

};

#endif // BUILDING_H
