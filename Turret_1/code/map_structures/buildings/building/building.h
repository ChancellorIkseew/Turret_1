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

	int tileX, tileY;

	static inline sf::Image buildingsImage;
	static inline sf::Texture buildingsTexture;
	static inline sf::Sprite buildingSprite;

public:

	int type;
	short durability;
	short size;

	std::list<StoredResource> storedResourcesList;

public:

	Building(int v_type, short v_durability, short v_size, int tileCoordX, int tileCoordY);
	Building(); // refactor
	virtual ~Building();

	virtual void save(std::ofstream& fout);
	virtual void load(std::ifstream& fin);

	virtual void interact();

	// resouses_and_inventory
	virtual bool canAccept(int resType);
	virtual bool isThisPositionFree(int position);
	virtual void leavePosition(int position);
	virtual void takePosition(int position);

	void addToInventory(int resType, short amount);
	virtual void placeResourceUnit(int type);

	int findResource();
	bool isEnoughRes(int v_type, short amount);
	void wasteResorce(int v_type, int amount);

	bool hasCorrectConveyerUp(int tileX, int tileY);
	bool hasCorrectConveyerLeft(int tileX, int tileY);
	bool hasCorrectConveyerDown(int tileX, int tileY);
	bool hasCorrectConveyerRight(int tileX, int tileY);

	// turrets
	virtual void setTurret(int turretType);
	virtual void removeTurret();
	virtual bool isTurretOnTower();

	// visual
	static void prepareSprites();
	virtual void animation();
	virtual void draw(sf::RenderWindow& window);

};


#endif // BUILDING_H
