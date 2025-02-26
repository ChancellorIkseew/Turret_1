
#include "building.h"
#include "buildings_enum.h"

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"


Building::Building(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	durability(durability), size(size), tile(tile), team(team) { }

void Building::save(cereal::BinaryOutputArchive& archive) const
{
	int teamID = team->getID();
	archive(durability, size, direction, tile, teamID);
}

void Building::load(cereal::BinaryInputArchive& archive)
{
	int teamID;
	archive(durability, size, direction, tile, teamID);
	team = world->getTeam(teamID);
}


void Building::interact() { }

void Building::setDamage(const int16_t damage) {
	this->durability -= damage;
}
void Building::setDamage(const float damage) {
	this->durability -= static_cast<int>(damage);
}
void Building::setDurability(const int16_t durability) {
	this->durability = durability;
}

int Building::getTeamID() const { return team->getID(); }

// resUnits_and_inventory
bool Building::canAccept(const ResType resType) const { return false; }
bool Building::canAccept(const ResourceUnit& unit) const
{
	return canAccept(unit.type);
}


bool Building::isStorageFull(const short capacity) const
{
	short comonResQuant = 0;

	for (auto it = inventory.cbegin(); it != inventory.cend(); ++it)
	{
		comonResQuant += it->quantity;
	}

	if (comonResQuant < capacity)
		return false;
	return true;
}

ResType Building::findResource() const
{
	for (auto it = inventory.cbegin(); it != inventory.cend(); ++it)
	{
		if (it->quantity > 0)
			return it->type;
	}
	return ResType::NO_RESOURCES;
}

bool Building::isEnoughRes(const ResType resType, const uint16_t amount) const
{
	for (auto it = inventory.cbegin(); it != inventory.cend(); ++it)
	{
		if (it->type == resType && it->quantity >= amount)
			return true;
	}
	return false;
}

void Building::wasteResorce(const ResType resType, const uint16_t amount)
{
	for (auto it = inventory.begin(); it != inventory.end(); ++it)
	{
		if (it->type == resType)
		{
			it->quantity -= amount;
			return;
		}
	}
}

void Building::addToInventory(const ResType resType, const uint16_t amount)
{
	for (auto it = inventory.begin(); it != inventory.end(); ++it)
	{
		if (it->type == resType)
		{
			it->quantity += amount;
			return;
		}
	}
	inventory.emplace_back(StoredResource{ resType, amount });
}



bool Building::hasCorrectConveyerUp(const TileCoord tile, const BuildingsMap& buildingsMap) const
{
	const TileCoord checkTile = { tile.x, tile.y - 1 };
	return ((buildingsMap.getBuildingType(checkTile) == BuildingType::STANDARD_CONVEYER && buildingsMap.getBuildingDirection(checkTile) != 's') ||
		buildingsMap.getBuildingDirection(checkTile) == 'w');
}

bool Building::hasCorrectConveyerLeft(const TileCoord tile, const BuildingsMap& buildingsMap) const
{
	const TileCoord checkTile = { tile.x - 1, tile.y };
	return ((buildingsMap.getBuildingType(checkTile) == BuildingType::STANDARD_CONVEYER && buildingsMap.getBuildingDirection(checkTile) != 'd') ||
		buildingsMap.getBuildingDirection(checkTile) == 'a');
}

bool Building::hasCorrectConveyerDown(const TileCoord tile, const BuildingsMap& buildingsMap) const
{
	const TileCoord checkTile = { tile.x, tile.y + 1 };
	return ((buildingsMap.getBuildingType(checkTile) == BuildingType::STANDARD_CONVEYER && buildingsMap.getBuildingDirection(checkTile) != 'w') ||
		buildingsMap.getBuildingDirection(checkTile) == 's');
}

bool Building::hasCorrectConveyerRight(const TileCoord tile, const BuildingsMap& buildingsMap) const
{
	const TileCoord checkTile = { tile.x + 1, tile.y };
	return ((buildingsMap.getBuildingType(checkTile) == BuildingType::STANDARD_CONVEYER && buildingsMap.getBuildingDirection(checkTile) != 'a') ||
		buildingsMap.getBuildingDirection(checkTile) == 'd');
}


// resUnits_and_inventory
void Building::placeResourceUnit(const ResType resType, const TileCoord tile, BuildingsMap& buildingsMap)
{
	if (!isEnoughRes(resType, 1))
		return;

	int side = rand() % 4;
	int i = 0;
	TileCoord cheekTile(0, 0);
	ResourceUnit unit;

	while (true)
	{
		switch (side)
		{
		case 0:
			if (++i > 4)
				return;
			cheekTile = TileCoord(tile.x, tile.y - 1);
			unit = ResourceUnit(resType, 'w', PixelCoord(0, 12));
			if (side == 0 && hasCorrectConveyerUp(tile, buildingsMap) &&
				buildingsMap.canAccept(unit, cheekTile) && isEnoughRes(resType, 1))
			{
				buildingsMap.addToInventory(unit, cheekTile);
				wasteResorce(resType, 1);
			}
			[[fallthrough]];
		case 1:
			if (++i > 4)
				return;
			cheekTile = TileCoord(tile.x - 1, tile.y);
			unit = ResourceUnit(resType, 'a', PixelCoord(12, 0));
			if (side == 1 && hasCorrectConveyerLeft(tile, buildingsMap) &&
				buildingsMap.canAccept(unit, cheekTile) && isEnoughRes(resType, 1))
			{
				buildingsMap.addToInventory(unit, cheekTile);
				wasteResorce(resType, 1);
			}
			[[fallthrough]];
		case 2:
			if (++i > 4)
				return;
			cheekTile = TileCoord(tile.x, tile.y + 1);
			unit = ResourceUnit(resType, 's', PixelCoord(0, -12));
			if (side == 2 && hasCorrectConveyerDown(tile, buildingsMap) &&
				buildingsMap.canAccept(unit, cheekTile) && isEnoughRes(resType, 1))
			{
				buildingsMap.addToInventory(unit, cheekTile);
				wasteResorce(resType, 1);
			}
			[[fallthrough]];
		case 3:
			if (++i > 4)
				return;
			cheekTile = TileCoord(tile.x + 1, tile.y);
			unit = ResourceUnit(resType, 'd', PixelCoord(- 12, 0));
			if (side == 3 && hasCorrectConveyerRight(tile, buildingsMap) &&
				buildingsMap.canAccept(unit, cheekTile) && isEnoughRes(resType, 1))
			{
				buildingsMap.addToInventory(unit, cheekTile);
				wasteResorce(resType, 1);
			}
		}

		side = 0;
	}
}

void Building::placeResourceUnitX1(const ResType resType, BuildingsMap& buildingsMap)
{
	placeResourceUnit(resType, tile, buildingsMap);
}

void Building::placeResourceUnitX4(const ResType resType, BuildingsMap& buildingsMap)
{
	if (!isEnoughRes(resType, 1))
		return;
	for (int i = 0; i < 4; ++i)
	{
		TileCoord tryTile = tile + t1::be::coordSquareArr[i];
		placeResourceUnit(resType, tile, buildingsMap);
	}
}

void Building::placeResourceUnitX9(const ResType resType, BuildingsMap& buildingsMap)
{
	if (!isEnoughRes(resType, 1))
		return;
	for (int i = 0; i < 9; (i != 3 ? ++i : i += 2))
	{
		TileCoord tryTile = tile + t1::be::coordSquareArr[i];
		placeResourceUnit(resType, tile, buildingsMap);
	}
}

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
