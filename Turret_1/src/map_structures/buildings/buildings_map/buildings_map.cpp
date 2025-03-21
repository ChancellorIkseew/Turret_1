
#include "buildings_map.h"

#include "map_structures/buildings/building/building.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "map_structures/buildings/building_types/logistics/conveyer.h"

#include "game_interface/gameplay/gameplay_util/camera.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/team/team.h"

#include "t1_system/events/events_handler.h"


BuildingsMap::BuildingsMap(const TileCoord mapSize) : mapSize(mapSize)
{
	buildingsMap.resize(mapSize.x);
	for (auto& line : buildingsMap)
		line.resize(mapSize.y);
}


bool BuildingsMap::buildingExists(const int tileX, const int tileY) const {
	return (tileX >= 0 && tileX < mapSize.x && tileY >= 0 && tileY < mapSize.y &&
		buildingsMap[tileX][tileY] != nullptr);
}
bool BuildingsMap::isVoidBuilding(const int tileX, const int tileY) const {
	return (tileX >= 0 && tileX < mapSize.x && tileY >= 0 && tileY < mapSize.y &&
		buildingsMap[tileX][tileY] == nullptr);
}
bool BuildingsMap::buildingExists(const TileCoord tile) const {
	return buildingExists(tile.x, tile.y);
}
bool BuildingsMap::isVoidBuilding(const TileCoord tile) const {
	return isVoidBuilding(tile.x, tile.y);
}



std::list<StoredResource> BuildingsMap::getInventory(const TileCoord tile) const
{
	if (!buildingExists(tile))
	{
		std::list<StoredResource> nullInventory;
		return nullInventory;
	}
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->getInventory();
}


void BuildingsMap::intetract()
{
	for (auto& line : buildingsMap)
	{
		for (auto& building : line)
		{
			if (building != nullptr && building->getType() != BuildingType::AUXILARY)
				building->interact();
		}
	}
}

void BuildingsMap::pushChanges()
{
	if (justChangedTiles.empty())
		return;
	EventsHandler::pushEvent(t1::EventType::MAP_CHANGED, std::make_unique<t1::MapChanged>(justChangedTiles));
	justChangedTiles.clear();
}

const std::vector<std::shared_ptr<Building>>& BuildingsMap::getCores() const
{
	return cores;
}


void BuildingsMap::addToInventory(const ResType resType, const TileCoord tile)
{
	if (!buildingExists(tile))
		return;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	buildingsMap[mainTile.x][mainTile.y]->addToInventory(resType, 1);
}

void BuildingsMap::addToInventory(ResourceUnit& unit, const TileCoord tile)
{
	if (!buildingExists(tile))
		return;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	buildingsMap[mainTile.x][mainTile.y]->addToInventory(unit);
}

bool BuildingsMap::canAccept(const ResType resType, const TileCoord tile) const
{
	if (!buildingExists(tile))
		return false;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->canAccept(resType);
}

bool BuildingsMap::canAccept(const ResourceUnit& unit, const TileCoord tile) const
{
	if (!buildingExists(tile))
		return false;
	TileCoord mainTile = getBuildingMainTileCoord(tile);
	return buildingsMap[mainTile.x][mainTile.y]->canAccept(unit);
}


void BuildingsMap::draw(sf::RenderWindow& window, const Camera& camera)
{
	const TileCoord start = camera.getStartTile();
	const TileCoord end = camera.getEndTile();

	for (int x = start.x; x < end.x; ++x)
	{
		for (int y = start.y; y < end.y; ++y)
		{
			if (buildingsMap[x][y] != nullptr && buildingsMap[x][y]->getType() != BuildingType::AUXILARY)
				buildingsMap[x][y]->draw(window);
		}
	}

	for (int x = start.x; x < end.x; ++x)
	{
		for (int y = start.y; y < end.y; ++y)
		{
			if (buildingsMap[x][y] == nullptr)
				continue;
			const BuildingType type = buildingsMap[x][y]->getType();
			if (type != BuildingType::STANDARD_CONVEYER && type != BuildingType::SHIELDED_CONVEYER)
				continue;
			Conveyer* conveyer = static_cast<Conveyer*>(buildingsMap[x][y].get());
			conveyer->drawResources(window);
		}
	}
}
