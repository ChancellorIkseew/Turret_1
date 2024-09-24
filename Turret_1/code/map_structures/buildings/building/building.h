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
	short quant;
};

class Building
{
protected:
	TileCoord tile;

	static inline sf::Image buildingsImage;
	static inline sf::Texture buildingsTexture;
	static inline sf::Sprite buildingSprite;

public:
	int type;
	short durability;
	short size;

	std::list<StoredResource> storedResourcesList;

public:
	Building(int type, short durability, short size, const TileCoord tile);
	Building() = default;
	virtual ~Building();

	virtual void save(std::ofstream& fout) const;
	virtual void load(std::ifstream& fin);

	static Building* setBuilding(int type, char direction, short durability, short v_size, const TileCoord tile);
	static Building* createBuilding(int type);

	virtual void interact();
	void setDamage(const int damage);
	TileCoord getTileCoord() const;

	// resouses_and_inventory
	virtual bool canAccept(const int resType) const;
	virtual bool isThisPositionFree(const int position) const;
	virtual void leavePosition(const int position);
	virtual void takePosition(const int position);

	void addToInventory(const int resType, const short amount);

	int findResource() const;
	bool isEnoughRes(const int resType, const short amount) const;
	void wasteResorce(const int resType, const int amount);

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

private:
	void placeResourceUnit(const int resType, const TileCoord tile);
protected:
	void placeResourceUnitX1(const int resType);
	void placeResourceUnitX4(const int resType);
	void placeResourceUnitX9(const int resType);

};


#endif // BUILDING_H
