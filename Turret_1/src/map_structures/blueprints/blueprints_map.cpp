
#include "blueprints_map.h"
#include "game_interface/gameplay/gameplay_util/camera.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"

BlueprintsMap::BlueprintsMap(const TileCoord mapSize) : mapSize(mapSize)
{
	blueprintsMap.resize(mapSize.x);
	for (auto& line : blueprintsMap)
		line.resize(mapSize.y);
}

bool BlueprintsMap::tileExists(const TileCoord tile) const {
	return tile.x >= 0 && tile.x < mapSize.x && tile.y >= 0 && tile.y < mapSize.y;
}
bool BlueprintsMap::isVoidTile(const TileCoord tile) const {
	return tileExists(tile) && blueprintsMap[tile.x][tile.y].type == BuildingType::VOID_;
}
bool BlueprintsMap::isFilledTile(const TileCoord tile) const {
	return tileExists(tile) && blueprintsMap[tile.x][tile.y].type != BuildingType::VOID_;
}

void BlueprintsMap::placeBlueprint(const BuildingType type, const char direction, const TileCoord tile)
{
	if (!tileExists(tile))
		return;
	blueprintsMap[tile.x][tile.y].type = type;
	blueprintsMap[tile.x][tile.y].direction = direction;
}

void BlueprintsMap::constructBuilding(BuildingsMap& buildingsMap, const TileCoord tile)
{
	if (!tileExists(tile))
		return;
	buildingsMap.constructBuilding(blueprintsMap[tile.x][tile.y].type, blueprintsMap[tile.x][tile.y].direction, tile, player);
	blueprintsMap[tile.x][tile.y].type = BuildingType::VOID_;
}

BuildingType BlueprintsMap::getType(const TileCoord tile) const
{
	if (!tileExists(tile))
		return BuildingType::VOID_;
	return blueprintsMap[tile.x][tile.y].type;
}


void BlueprintsMap::draw(sf::RenderWindow& window, const Camera& camera)
{
	const TileCoord start = camera.getStartTile();
	const TileCoord end = camera.getEndTile();

	for (int x = start.x; x < end.x; ++x)
	{
		for (int y = start.y; y < end.y; ++y)
		{
			if (blueprintsMap[x][y].type == BuildingType::VOID_)
				continue;
			buildExample.setTextureRect(t1::bc::buildingsInfoTable.at(blueprintsMap[x][y].type).icoRect);
			buildExample.setPosition(sf::Vector2f(x * _TILE_ , y * _TILE_));
			window.draw(buildExample);
		}
	}
}

void BlueprintsMap::prepareSprites()
{
	buildingsImage.loadFromFile("images/buildings_ico.bmp");
	buildingsImage.createMaskFromColor(sf::Color(0, 255, 0));
	buildingsTexture.loadFromImage(buildingsImage);
	buildExample.setColor(sf::Color(128, 128, 225, 128));
}