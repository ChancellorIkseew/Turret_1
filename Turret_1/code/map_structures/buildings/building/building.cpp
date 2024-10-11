
#include "building.h"
#include "buildings_enum.h"

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/resources/resource_units.h"


Building::Building(int type, short durability, short size, const TileCoord tile)
{
	this->type = type;
	this->durability = durability;
	this->size = size;
	this->direction = 0;

	this->tile = tile;
}


void Building::save(std::ofstream& fout)const
{
	fout << size << " " << durability << '\n';

	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		if (it->quantity != 0)
			fout << it->type << " " << it->quantity << '\n';
	}
	fout << "$\n";
}

void Building::load(std::ifstream& fin)
{
	fin >> size >> durability;

	while (true)
	{
		char nextSymbol;
		fin >> nextSymbol;
		
		if (nextSymbol == '$')
			break;

		fin.seekg(-1, std::ios::cur);
		int resType;
		short amount;
		fin >> resType >> amount;
		storedResourcesList.push_back(StoredResource{ resType, amount });	
	}
}


void Building::interact() { }

void Building::setDamage(const int damage)
{
	this->durability -= damage;
}

void Building::setDurability(const int durability)
{
	this->durability = durability;
}

TileCoord Building::getTileCoord() const { return tile; }
int Building::getType() const { return type; }
short Building::getSize() const { return size; }
short Building::getDurability() const { return durability; }
char Building::getDirection() const { return direction;  }


// resUnits_and_inventory
bool Building::canAccept(const int resType) const { return false; }
bool Building::isThisPositionFree(const int position) const { return false; }
void Building::leavePosition(const int position) { }
void Building::takePosition(const int position) { }

bool Building::isStorageFull(const short capacity) const
{
	short comonResQuant = 0;

	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		comonResQuant += it->quantity;
	}

	if (comonResQuant < capacity)
		return false;
	return true;
}

int Building::findResource() const
{
	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		if (it->quantity > 0)
			return it->type;
	}
	return RES_NO_RESOURCES;
}

bool Building::isEnoughRes(const int resType, const short amount) const
{
	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		if (it->type == resType && it->quantity >= amount)
			return true;
	}
	return false;
}

void Building::wasteResorce(const int resType, const short amount)
{
	for (auto it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		if (it->type == resType)
		{
			it->quantity -= amount;
			return;
		}
	}
}

void Building::addToInventory(const int resType, const short amount)
{
	for (auto it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		if (it->type == resType)
		{
			it->quantity += amount;
			return;
		}
	}
	storedResourcesList.emplace_back(StoredResource{ resType, amount });
}



bool Building::hasCorrectConveyerUp(const TileCoord tile) const
{
	const TileCoord checkTile = { tile.x, tile.y - 1 };
	return ((BuildingsMap::getBuildingType(checkTile) == STANDARD_CONVEYER && BuildingsMap::getBuildingDirection(checkTile) != 's') ||
		BuildingsMap::getBuildingDirection(checkTile) == 'w');
}

bool Building::hasCorrectConveyerLeft(const TileCoord tile) const
{
	const TileCoord checkTile = { tile.x - 1, tile.y };
	return ((BuildingsMap::getBuildingType(checkTile) == STANDARD_CONVEYER && BuildingsMap::getBuildingDirection(checkTile) != 'd') ||
		BuildingsMap::getBuildingDirection(checkTile) == 'a');
}

bool Building::hasCorrectConveyerDown(const TileCoord tile) const
{
	const TileCoord checkTile = { tile.x, tile.y + 1 };
	return ((BuildingsMap::getBuildingType(checkTile) == STANDARD_CONVEYER && BuildingsMap::getBuildingDirection(checkTile) != 'w') ||
		BuildingsMap::getBuildingDirection(checkTile) == 's');
}

bool Building::hasCorrectConveyerRight(const TileCoord tile) const
{
	const TileCoord checkTile = { tile.x + 1, tile.y };
	return ((BuildingsMap::getBuildingType(checkTile) == STANDARD_CONVEYER && BuildingsMap::getBuildingDirection(checkTile) != 'a') ||
		BuildingsMap::getBuildingDirection(checkTile) == 'd');
}


// resUnits_and_inventory
void Building::placeResourceUnit(const int resType, const TileCoord tile)
{
	if (!isEnoughRes(resType, 1))
		return;

	int side = rand() % 4;
	int i = 0;

	while (true)
	{
		switch (side)
		{
		case 0:
			if (++i > 4)
				return;
			if (side == 0 && hasCorrectConveyerUp(tile) &&
				BuildingsMap::isThisPositionFree({ tile.x, tile.y - 1 }, 2) && isEnoughRes(resType, 1))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tile.x * _TILE_ + _HALF_TILE_, tile.y * _TILE_ - 6, 'w'));
				BuildingsMap::takePosition({ tile.x, tile.y - 1 }, 2);
				wasteResorce(resType, 1);
			}
			[[fallthrough]];
		case 1:
			if (++i > 4)
				return;
			if (side == 1 && hasCorrectConveyerLeft(tile) &&
				BuildingsMap::isThisPositionFree({ tile.x - 1, tile.y }, 4) && isEnoughRes(resType, 1))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tile.x * _TILE_ - 6, tile.y * _TILE_ + _HALF_TILE_, 'a'));
				BuildingsMap::takePosition({ tile.x - 1, tile.y }, 4);
				wasteResorce(resType, 1);
			}
			[[fallthrough]];
		case 2:
			if (++i > 4)
				return;
			if (side == 2 && hasCorrectConveyerDown(tile) &&
				BuildingsMap::isThisPositionFree({ tile.x, tile.y + 1 }, 0) && isEnoughRes(resType, 1))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tile.x * _TILE_ + _HALF_TILE_, tile.y * _TILE_ + 38, 's'));
				BuildingsMap::takePosition({ tile.x, tile.y + 1 }, 0);
				wasteResorce(resType, 1);
			}
			[[fallthrough]];
		case 3:
			if (++i > 4)
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
		int tileX = this->tile.x + t1::be::coordSquareArr[i].x;
		int tileY = this->tile.y + t1::be::coordSquareArr[i].y;

		placeResourceUnit(resType, { tileX, tileY });
	}
}

void Building::placeResourceUnitX9(const int resType)
{
	if (!isEnoughRes(resType, 1))
		return;

	for (int i = 0; i < 9; (i != 3 ? ++i : i += 2))
	{
		int tileX = this->tile.x + t1::be::coordSquareArr[i].x;
		int tileY = this->tile.y + t1::be::coordSquareArr[i].y;

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
