
#include "building.h"
#include "buildings_enum.h"
#include <cereal/types/list.hpp>

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"


Building::Building(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	durability(durability), size(size), tile(tile), team(team) { }

void Building::save(cereal::BinaryOutputArchive& archive) const
{
	int teamID = team->getID();
	archive(durability, size, direction, tile, teamID, inventory);
}

void Building::load(cereal::BinaryInputArchive& archive)
{
	int teamID;
	archive(durability, size, direction, tile, teamID, inventory);
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
	for (auto& res : inventory)
	{
		comonResQuant += res.quantity;
	}
	return comonResQuant >= capacity;
}

ResType Building::findResource() const
{
	for (auto& res : inventory)
	{
		if (res.quantity > 0)
			return res.type;
	}
	return ResType::NO_RESOURCES;
}

bool Building::isEnoughRes(const ResType resType, const uint16_t amount) const
{
	for (auto& res : inventory)
	{
		if (res.type != resType)
			continue;
		if (res.quantity >= amount)
			return true;
	}
	return false;
}

void Building::wasteResorce(const ResType resType, const uint16_t amount)
{
	for (auto& res : inventory)
	{
		if (res.type != resType)
			continue;
		res.quantity -= amount;
		return;
	}
}

void Building::addToInventory(const ResType resType, const uint16_t amount)
{
	for (auto& res : inventory)
	{
		if (res.type != resType)
			continue;
		res.quantity += amount;
		return;
	}
	inventory.emplace_back(resType, amount);
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
}

void Building::animation() { }
