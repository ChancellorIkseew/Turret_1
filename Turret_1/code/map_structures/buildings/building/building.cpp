
#include "building.h"
#include "buildings_enum.h"

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/team/team.h"


Building::Building(int type, short durability, short size, const TileCoord tile, Team* team)
{
	this->type = type;
	this->durability = durability;
	this->size = size;
	this->direction = 0;
	this->team = team;

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
		uint16_t resType;
		uint16_t amount;
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
Team* Building::getTeam() const { return team; }
int Building::getTeamID() const { return team->getID(); }


// resUnits_and_inventory
bool Building::canAccept(const uint16_t resType) const { return false; }
bool Building::canAccept(const ResourceUnit& unit) const { return false; }


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

bool Building::isEnoughRes(const uint16_t resType, const uint16_t amount) const
{
	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		if (it->type == resType && it->quantity >= amount)
			return true;
	}
	return false;
}

void Building::wasteResorce(const uint16_t resType, const uint16_t amount)
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

void Building::addToInventory(const uint16_t resType, const uint16_t amount)
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
	TileCoord cheekTile = { 0.0f, 0.0f };
	ResourceUnit unit;

	while (true)
	{
		switch (side)
		{
		case 0:
			if (++i > 4)
				return;
			cheekTile = { tile.x, tile.y - 1 };
			unit = ResourceUnit(resType, 'w', { 0, 12 });
			if (side == 0 && hasCorrectConveyerUp(tile) &&
				BuildingsMap::canAccept(unit, cheekTile) && isEnoughRes(resType, 1))
			{
				BuildingsMap::addToInventory(unit, cheekTile);
				wasteResorce(resType, 1);
			}
			[[fallthrough]];
		case 1:
			if (++i > 4)
				return;
			cheekTile = { tile.x - 1, tile.y };
			unit = ResourceUnit(resType, 'a', { 12, 0 });
			if (side == 1 && hasCorrectConveyerLeft(tile) &&
				BuildingsMap::canAccept(unit, cheekTile) && isEnoughRes(resType, 1))
			{
				BuildingsMap::addToInventory(unit, cheekTile);
				wasteResorce(resType, 1);
			}
			[[fallthrough]];
		case 2:
			if (++i > 4)
				return;
			cheekTile = { tile.x, tile.y + 1 };
			unit = ResourceUnit(resType, 's', { 0, -12 });
			if (side == 2 && hasCorrectConveyerDown(tile) &&
				BuildingsMap::canAccept(unit, cheekTile) && isEnoughRes(resType, 1))
			{
				BuildingsMap::addToInventory(unit, cheekTile);
				wasteResorce(resType, 1);
			}
			[[fallthrough]];
		case 3:
			if (++i > 4)
				return;
			cheekTile = { tile.x + 1, tile.y };
			unit = ResourceUnit(resType, 'd', { -12, 0 });
			if (side == 3 && hasCorrectConveyerRight(tile) &&
				BuildingsMap::canAccept(unit, cheekTile) && isEnoughRes(resType, 1))
			{
				BuildingsMap::addToInventory(unit, cheekTile);
				wasteResorce(resType, 1);
			}
		}

		side = 0;
	}
}

void Building::placeResourceUnitX1(const uint16_t resType)
{
	placeResourceUnit(resType, this->tile);
}

void Building::placeResourceUnitX4(const uint16_t resType)
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

void Building::placeResourceUnitX9(const uint16_t resType)
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
// conveyers
void Building::addToInventory(ResourceUnit& unit)
{
	addToInventory(unit.type, 1);
}

// visual
void Building::prepareSprites()
{
	buildingsImage.loadFromFile("images/buildings_map.bmp");
	buildingsImage.createMaskFromColor(sf::Color(0, 255, 0));
	buildingsTexture.loadFromImage(buildingsImage);
	buildingSprite.setTexture(buildingsTexture);
}

void Building::animation() { }
