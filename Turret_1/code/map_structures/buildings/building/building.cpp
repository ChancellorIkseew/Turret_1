
#include "building.h"
#include "buildings_enum.h"

#include "../buildings_map.h"
#include "../../resources/res_enum.h"


Building::Building(int v_type, short v_durability, short v_size, int tileX, int tileY)
{
	type = v_type;
	durability = v_durability;
	size = v_size;

	this->tileX = tileX;
	this->tileY = tileY;
}

Building::Building() { }

Building::~Building()
{
	storedResourcesList.clear();
}



void Building::save(std::ofstream& fout)
{
	fout << type << " " << size << " " << durability <<
		" " << tileX << " " << tileY << '\n';

	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		if(it->quant != 0)
			fout << it->type << " " << it->quant << '\n';
	}

	fout << "$\n";
}


void Building::load(std::ifstream& fin)
{
	fin >> size >> durability >> tileX >> tileY;

	while (true)
	{
		char nextSymbol;
		fin >> nextSymbol;
		
		if (nextSymbol != '$')
		{
			fin.seekg(-1, std::ios::cur);
			int resType;
			fin >> resType;
			short amount;
			fin >> amount;
			storedResourcesList.push_back(StoredResource{ resType, amount });
		}
		else
		{
			break;
		}
	}
}


void Building::interact() { }


// resUnits_and_inventory
void Building::addToInventory(int resType, short amount)
{
	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		if (it->type == resType)
		{
			it->quant = it->quant + amount;

			//std::cout << "resource was accepted; ";
			//std::cout << " resource_quant: " << (*it)->quant;
			//std::cout << "; resource_type: " << (*it)->type << '\n';
			return;
		}
	}

	storedResourcesList.emplace_back(StoredResource{ resType, amount });
	//std::cout << "new resource_obj created" << '\n';
}



int Building::findResource()
{
	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		if (it->quant > 0)
		{
			//std::cout << "detected_resource_quant:" << (*it)->quant << '\n';
			return it->type;
		}
	}

	return RES_NO_RESOURCES;
}



bool Building::isEnoughRes(int v_type, short amount)
{
	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		if (it->type == v_type && it->quant >= amount)
		{
			//std::cout << "detected_resource_type:" << (*it)->type << '\n';
			return true;
		}
	}

	return false;
}



void Building::wasteResorce(int v_type, int amount)
{
	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		if (it->type == v_type)
		{
			it->quant = it->quant - amount;
			//std::cout << "resource_wasted:" << (*it)->type << '\n';
			return;
		}
	}

	return;
}



bool Building::hasCorrectConveyerUp(int tileX, int tileY)
{
	return (BuildingsMap::getBuildingType(tileX, tileY - 1) == STANDARD_CONVEYER_UP || 
		BuildingsMap::getBuildingType(tileX, tileY - 1) == STANDARD_CONVEYER_LEFT || 
		BuildingsMap::getBuildingType(tileX, tileY - 1) == STANDARD_CONVEYER_RIGHT ||
		BuildingsMap::getBuildingType(tileX, tileY - 1) == SHIELDED_CONVEYER_UP);
}

bool Building::hasCorrectConveyerLeft(int tileX, int tileY)
{
	return (BuildingsMap::getBuildingType(tileX - 1, tileY) == STANDARD_CONVEYER_UP || 
		BuildingsMap::getBuildingType(tileX - 1, tileY) == STANDARD_CONVEYER_LEFT || 
		BuildingsMap::getBuildingType(tileX - 1, tileY) == STANDARD_CONVEYER_DOWN ||
		BuildingsMap::getBuildingType(tileX - 1, tileY) == SHIELDED_CONVEYER_LEFT);
}

bool Building::hasCorrectConveyerDown(int tileX, int tileY)
{
	return (BuildingsMap::getBuildingType(tileX, tileY + 1) == STANDARD_CONVEYER_LEFT ||
		BuildingsMap::getBuildingType(tileX, tileY + 1) == STANDARD_CONVEYER_DOWN ||
		BuildingsMap::getBuildingType(tileX, tileY + 1) == STANDARD_CONVEYER_RIGHT ||
		BuildingsMap::getBuildingType(tileX, tileY + 1) == SHIELDED_CONVEYER_DOWN);
}

bool Building::hasCorrectConveyerRight(int tileX, int tileY)
{
	return (BuildingsMap::getBuildingType(tileX + 1, tileY) == STANDARD_CONVEYER_UP || 
		BuildingsMap::getBuildingType(tileX + 1, tileY) == STANDARD_CONVEYER_DOWN || 
		BuildingsMap::getBuildingType(tileX + 1, tileY) == STANDARD_CONVEYER_RIGHT ||
		BuildingsMap::getBuildingType(tileX + 1, tileY) == SHIELDED_CONVEYER_RIGHT);
}


// resUnits_and_inventory
bool Building::canAccept(int resType) { return false; }
bool Building::isThisPositionFree(int position) { return false; }
void Building::leavePosition(int position) { }
void Building::takePosition(int position) { }

void Building::placeResourceUnit(int type) { }

// turrets
void Building::setTurret(int turretType) { }
void Building::removeTurret() { }
bool Building::isTurretOnTower() { return false; }

// visual
void Building::prepareSprites()
{
	buildingsImage.loadFromFile("images/buildings_map.bmp");
	buildingsImage.createMaskFromColor(sf::Color(0, 255, 0));
	buildingsTexture.loadFromImage(buildingsImage);
	buildingSprite.setTexture(buildingsTexture);
}

void Building::animation() { }
void Building::draw(sf::RenderWindow& window) { }
