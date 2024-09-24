
#include "building.h"
#include "buildings_enum.h"

#include "map_structures/buildings/buildings_map.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/resources/resource_units.h"


Building::Building(int type, short durability, short size, int tileX, int tileY)
{
	this->type = type;
	this->durability = durability;
	this->size = size;

	this->tileX = tileX;
	this->tileY = tileY;
}

Building::~Building()
{
	storedResourcesList.clear();
}



void Building::save(std::ofstream& fout)const
{
	fout << type << " " << size << " " << durability <<
		" " << tileX << " " << tileY << '\n';

	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		if (it->quant != 0)
		{
			fout << it->type << " " << it->quant << '\n';
		}	
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
		
		if (nextSymbol == '$')
		{
			break;
		}

		fin.seekg(-1, std::ios::cur);
		int resType;
		fin >> resType;
		short amount;
		fin >> amount;
		storedResourcesList.push_back(StoredResource{ resType, amount });	
	}
}


void Building::interact() { }

void Building::setDamage(const int damage)
{
	durability -= damage;
}


// resUnits_and_inventory
void Building::addToInventory(const int resType, const short amount)
{
	for (auto it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		if (it->type == resType)
		{
			it->quant = it->quant + amount;
			return;
		}
	}

	storedResourcesList.emplace_back(StoredResource{ resType, amount });
}



int Building::findResource() const
{
	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		if (it->quant > 0)
		{
			return it->type;
		}
	}

	return RES_NO_RESOURCES;
}



bool Building::isEnoughRes(const int resType, const short amount) const
{
	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		if (it->type == resType && it->quant >= amount)
		{
			return true;
		}
	}

	return false;
}



void Building::wasteResorce(const int resType, const int amount)
{
	for (auto it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		if (it->type == resType)
		{
			it->quant = it->quant - amount;
			return;
		}
	}
}



bool Building::hasCorrectConveyerUp(const int tileX, const int tileY) const
{
	return (BuildingsMap::getBuildingType(tileX, tileY - 1) == STANDARD_CONVEYER_UP || 
		BuildingsMap::getBuildingType(tileX, tileY - 1) == STANDARD_CONVEYER_LEFT || 
		BuildingsMap::getBuildingType(tileX, tileY - 1) == STANDARD_CONVEYER_RIGHT ||
		BuildingsMap::getBuildingType(tileX, tileY - 1) == SHIELDED_CONVEYER_UP);
}

bool Building::hasCorrectConveyerLeft(const int tileX, const int tileY) const
{
	return (BuildingsMap::getBuildingType(tileX - 1, tileY) == STANDARD_CONVEYER_UP || 
		BuildingsMap::getBuildingType(tileX - 1, tileY) == STANDARD_CONVEYER_LEFT || 
		BuildingsMap::getBuildingType(tileX - 1, tileY) == STANDARD_CONVEYER_DOWN ||
		BuildingsMap::getBuildingType(tileX - 1, tileY) == SHIELDED_CONVEYER_LEFT);
}

bool Building::hasCorrectConveyerDown(const int tileX, const int tileY) const
{
	return (BuildingsMap::getBuildingType(tileX, tileY + 1) == STANDARD_CONVEYER_LEFT ||
		BuildingsMap::getBuildingType(tileX, tileY + 1) == STANDARD_CONVEYER_DOWN ||
		BuildingsMap::getBuildingType(tileX, tileY + 1) == STANDARD_CONVEYER_RIGHT ||
		BuildingsMap::getBuildingType(tileX, tileY + 1) == SHIELDED_CONVEYER_DOWN);
}

bool Building::hasCorrectConveyerRight(const int tileX, const int tileY) const
{
	return (BuildingsMap::getBuildingType(tileX + 1, tileY) == STANDARD_CONVEYER_UP || 
		BuildingsMap::getBuildingType(tileX + 1, tileY) == STANDARD_CONVEYER_DOWN || 
		BuildingsMap::getBuildingType(tileX + 1, tileY) == STANDARD_CONVEYER_RIGHT ||
		BuildingsMap::getBuildingType(tileX + 1, tileY) == SHIELDED_CONVEYER_RIGHT);
}


// resUnits_and_inventory
bool Building::canAccept(const int resType) const { return false; }
bool Building::isThisPositionFree(const int position) const { return false; }
void Building::leavePosition(const int position) { }
void Building::takePosition(const int position) { }


void Building::placeResourceUnit(const int resType, const int tileX, const int tileY)
{
	if (!isEnoughRes(resType, 1))
		return;

	int side = rand() % 4;
	int j = 0;

	while (true)
	{
		switch (side)
		{
		case 0:
			if (++j > 4)
				return;
			if (side == 0 && hasCorrectConveyerUp(tileX, tileY) &&
				BuildingsMap::isThisPositionFree(tileX, tileY - 1, 2) && isEnoughRes(resType, 1))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tileX * _TILE_ + _HALF_TILE_, tileY * _TILE_ - 6, 'w'));
				BuildingsMap::takePosition(tileX, tileY - 1, 2);
				wasteResorce(resType, 1);
			}

		case 1:
			if (++j > 4)
				return;
			if (side == 1 && hasCorrectConveyerLeft(tileX, tileY) &&
				BuildingsMap::isThisPositionFree(tileX - 1, tileY, 4) && isEnoughRes(resType, 1))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tileX * _TILE_ - 6, tileY * _TILE_ + _HALF_TILE_, 'a'));
				BuildingsMap::takePosition(tileX - 1, tileY, 4);
				wasteResorce(resType, 1);
			}

		case 2:
			if (++j > 4)
				return;
			if (side == 2 && hasCorrectConveyerDown(tileX, tileY) &&
				BuildingsMap::isThisPositionFree(tileX, tileY + 1, 0) && isEnoughRes(resType, 1))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tileX * _TILE_ + _HALF_TILE_, tileY * _TILE_ + 38, 's'));
				BuildingsMap::takePosition(tileX, tileY + 1, 0);
				wasteResorce(resType, 1);
			}

		case 3:
			if (++j > 4)
				return;
			if (side == 3 && hasCorrectConveyerRight(tileX, tileY) &&
				BuildingsMap::isThisPositionFree(tileX + 1, tileY, 3) && isEnoughRes(resType, 1))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tileX * _TILE_ + 38, tileY * _TILE_ + _HALF_TILE_, 'd'));
				BuildingsMap::takePosition(tileX + 1, tileY, 3);
				wasteResorce(resType, 1);
			}
		}

		side = 0;
	}
}

void Building::placeResourceUnitX1(const int resType)
{
	placeResourceUnit(resType, this->tileX, this->tileY);
}

void Building::placeResourceUnitX4(const int resType)
{
	if (!isEnoughRes(resType, 1))
		return;

	for (int i = 0; i < 4; ++i)
	{
		int tileX = this->tileX + coordSquareArr[i].x;
		int tileY = this->tileY + coordSquareArr[i].y;

		placeResourceUnit(resType, tileX, tileY);
	}
}

void Building::placeResourceUnitX9(const int resType)
{
	if (!isEnoughRes(resType, 1))
		return;

	for (int i = 0; i < 9; (i != 3 ? ++i : i += 2))
	{
		int tileX = this->tileX + coordSquareArr[i].x;
		int tileY = this->tileY + coordSquareArr[i].y;

		placeResourceUnit(resType, tileX, tileY);
	}
}


// turrets
void Building::setTurret(const int turretType) { }
void Building::removeTurret() { }
bool Building::isTurretOnTower() const { return false; }

// visual
void Building::prepareSprites()
{
	buildingsImage.loadFromFile("images/buildings_map.bmp");
	buildingsImage.createMaskFromColor(sf::Color(0, 255, 0));
	buildingsTexture.loadFromImage(buildingsImage);
	buildingSprite.setTexture(buildingsTexture);
}

void Building::animation() { }
