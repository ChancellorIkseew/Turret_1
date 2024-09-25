#pragma once
#ifndef BUILDING_H
#define BUILDING_H

#include <list>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "map_structures/base_engine/tile_coord.h"
#include "map_structures/terrain/terrain.h"


struct StoredResource
{
	int type;
	short quantity;
};

class Building
{
private:
	int type;
	short durability;
	short size;
	std::list<StoredResource> storedResourcesList;

	void placeResourceUnit(const int resType, const TileCoord tile);

protected:
	TileCoord tile;
	char direction;

	static inline sf::Image buildingsImage;
	static inline sf::Texture buildingsTexture;
	static inline sf::Sprite buildingSprite;

	void placeResourceUnitX1(const int resType);
	void placeResourceUnitX4(const int resType);
	void placeResourceUnitX9(const int resType);
	bool isStorageFull(const short capacity) const;

public:
	Building(int type, short durability, short size, const TileCoord tile);
	virtual ~Building();

	virtual void save(std::ofstream& fout) const;
	virtual void load(std::ifstream& fin);

	static std::shared_ptr<Building> createBuilding(int type, char direction, short durability, short v_size, const TileCoord tile);

	virtual void interact();
	void setDamage(const int damage);
	void setDurability(const int durability);
	TileCoord getTileCoord() const;
	int getType() const;
	short getDurability() const;
	short getSize() const;
	char getDirection() const;

	// resouses_and_inventory
	virtual bool canAccept(const int resType) const;
	virtual bool isThisPositionFree(const int position) const;
	virtual void leavePosition(const int position);
	virtual void takePosition(const int position);

	int findResource() const;
	bool isEnoughRes(const int resType, const short amount) const;
	void wasteResorce(const int resType, const short amount);
	void addToInventory(const int resType, const short amount);

	// resUnits_and_inventory
	bool hasCorrectConveyerUp(const TileCoord tile) const;
	bool hasCorrectConveyerLeft(const TileCoord tile) const;
	bool hasCorrectConveyerDown(const TileCoord tile) const;
	bool hasCorrectConveyerRight(const TileCoord tile) const;

	// turrets
	virtual void setTurret(const int turretType);
	virtual void removeTurret();
	virtual bool isTurretOnTower() const;

	// visual
	static void prepareSprites();
	virtual void animation();
	virtual void draw(sf::RenderWindow& window) = 0;

};

#endif // BUILDING_H
