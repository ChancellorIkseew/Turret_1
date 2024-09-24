
#include "building.h"
#include "buildings_enum.h"

#include "map_structures/buildings/buildings_map.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/resources/resource_units.h"


Building::Building(int type, short durability, short size, const TileCoord tile)
{
	this->type = type;
	this->durability = durability;
	this->size = size;

	this->tile.x = tile.x;
	this->tile.y = tile.y;
}

Building::~Building()
{
	storedResourcesList.clear();
}



void Building::save(std::ofstream& fout)const
{
	fout << type << " " << size << " " << durability <<
		" " << tile.x << " " << tile.y << '\n';

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
	fin >> size >> durability >> tile.x >> tile.y;

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

TileCoord Building::getTileCoord() const
{
	return tile;
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



bool Building::hasCorrectConveyerUp(const TileCoord tile) const
{
	return (BuildingsMap::getBuildingType({ tile.x, tile.y - 1 }) == STANDARD_CONVEYER_UP ||
		BuildingsMap::getBuildingType({ tile.x, tile.y - 1 }) == STANDARD_CONVEYER_LEFT ||
		BuildingsMap::getBuildingType({ tile.x, tile.y - 1 }) == STANDARD_CONVEYER_RIGHT ||
		BuildingsMap::getBuildingType({ tile.x, tile.y - 1 }) == SHIELDED_CONVEYER_UP);
}

bool Building::hasCorrectConveyerLeft(const TileCoord tile) const
{
	return (BuildingsMap::getBuildingType({ tile.x - 1, tile.y }) == STANDARD_CONVEYER_UP ||
		BuildingsMap::getBuildingType({ tile.x - 1, tile.y }) == STANDARD_CONVEYER_LEFT ||
		BuildingsMap::getBuildingType({ tile.x - 1, tile.y }) == STANDARD_CONVEYER_DOWN ||
		BuildingsMap::getBuildingType({ tile.x - 1, tile.y }) == SHIELDED_CONVEYER_LEFT);
}

bool Building::hasCorrectConveyerDown(const TileCoord tile) const
{
	return (BuildingsMap::getBuildingType({ tile.x, tile.y + 1 }) == STANDARD_CONVEYER_LEFT ||
		BuildingsMap::getBuildingType({ tile.x, tile.y + 1 }) == STANDARD_CONVEYER_DOWN ||
		BuildingsMap::getBuildingType({ tile.x, tile.y + 1 }) == STANDARD_CONVEYER_RIGHT ||
		BuildingsMap::getBuildingType({ tile.x, tile.y + 1 }) == SHIELDED_CONVEYER_DOWN);
}

bool Building::hasCorrectConveyerRight(const TileCoord tile) const
{
	return (BuildingsMap::getBuildingType({ tile.x + 1, tile.y }) == STANDARD_CONVEYER_UP ||
		BuildingsMap::getBuildingType({ tile.x + 1, tile.y }) == STANDARD_CONVEYER_DOWN ||
		BuildingsMap::getBuildingType({ tile.x + 1, tile.y }) == STANDARD_CONVEYER_RIGHT ||
		BuildingsMap::getBuildingType({ tile.x + 1, tile.y }) == SHIELDED_CONVEYER_RIGHT);
}


// resUnits_and_inventory
bool Building::canAccept(const int resType) const { return false; }
bool Building::isThisPositionFree(const int position) const { return false; }
void Building::leavePosition(const int position) { }
void Building::takePosition(const int position) { }


void Building::placeResourceUnit(const int resType, const TileCoord tile)
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
			if (side == 0 && hasCorrectConveyerUp(tile) &&
				BuildingsMap::isThisPositionFree({ tile.x, tile.y - 1 }, 2) && isEnoughRes(resType, 1))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tile.x * _TILE_ + _HALF_TILE_, tile.y * _TILE_ - 6, 'w'));
				BuildingsMap::takePosition({ tile.x, tile.y - 1 }, 2);
				wasteResorce(resType, 1);
			}

		case 1:
			if (++j > 4)
				return;
			if (side == 1 && hasCorrectConveyerLeft(tile) &&
				BuildingsMap::isThisPositionFree({ tile.x - 1, tile.y }, 4) && isEnoughRes(resType, 1))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tile.x * _TILE_ - 6, tile.y * _TILE_ + _HALF_TILE_, 'a'));
				BuildingsMap::takePosition({ tile.x - 1, tile.y }, 4);
				wasteResorce(resType, 1);
			}

		case 2:
			if (++j > 4)
				return;
			if (side == 2 && hasCorrectConveyerDown(tile) &&
				BuildingsMap::isThisPositionFree({ tile.x, tile.y + 1 }, 0) && isEnoughRes(resType, 1))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tile.x * _TILE_ + _HALF_TILE_, tile.y * _TILE_ + 38, 's'));
				BuildingsMap::takePosition({ tile.x, tile.y + 1 }, 0);
				wasteResorce(resType, 1);
			}

		case 3:
			if (++j > 4)
				return;
			if (side == 3 && hasCorrectConveyerRight(tile) &&
				BuildingsMap::isThisPositionFree({ tile.x + 1, tile.y }, 3) && isEnoughRes(resType, 1))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tile.x * _TILE_ + 38, tile.y * _TILE_ + _HALF_TILE_, 'd'));
				BuildingsMap::takePosition({ tile.x + 1, tile.y }, 3);
				wasteResorce(resType, 1);
			}
		}

		side = 0;
	}
}

void Building::placeResourceUnitX1(const int resType)
{
	placeResourceUnit(resType, this->tile);
}

void Building::placeResourceUnitX4(const int resType)
{
	if (!isEnoughRes(resType, 1))
		return;

	for (int i = 0; i < 4; ++i)
	{
		int tileX = this->tile.x + coordSquareArr[i].x;
		int tileY = this->tile.y + coordSquareArr[i].y;

		placeResourceUnit(resType, { tileX, tileY });
	}
}

void Building::placeResourceUnitX9(const int resType)
{
	if (!isEnoughRes(resType, 1))
		return;

	for (int i = 0; i < 9; (i != 3 ? ++i : i += 2))
	{
		int tileX = this->tile.x + coordSquareArr[i].x;
		int tileY = this->tile.y + coordSquareArr[i].y;

		placeResourceUnit(resType, { tileX, tileY });
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
