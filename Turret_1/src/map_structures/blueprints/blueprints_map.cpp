
#include "blueprints_map.h"
#include "game_interface/gameplay/gameplay_util/camera.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"

#define map(tileForMap) blueprintsMap[tileForMap.x][tileForMap.y]
#define info(tileForInfo) t1::bc::buildingsInfoTable.at(map(tileForInfo).type)

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
	return tileExists(tile) && map(tile).type == BuildingType::VOID_;
}
bool BlueprintsMap::isFilledTile(const TileCoord tile) const {
	return tileExists(tile) && map(tile).type != BuildingType::VOID_;
}
bool BlueprintsMap::isMainTile(const TileCoord tile) const {
	return tileExists(tile) && map(tile).type != BuildingType::VOID_
							&& map(tile).type != BuildingType::AUXILARY;
}

bool BlueprintsMap::isAvaluablePlaceBlueprint(const BuildingType type, const TileCoord mainTile) const
{
	const uint8_t size = t1::bc::buildingsInfoTable.at(type).size;
	TileCoord checkTile;
	for (uint8_t i = 0; i < size; ++i)
	{
		checkTile = mainTile + t1::be::coordSquareArr[i];
		if (isFilledTile(checkTile))
			return false;
	}
	return true;
}

TileCoord BlueprintsMap::getMainTile(const TileCoord tile) const
{
	TileCoord checkTile;
	for (uint8_t i = 0; i < 16; ++i)
	{
		checkTile = tile - t1::be::coordSquareArr[i];
		if (isMainTile(checkTile))
			return checkTile;
	}
	return tile;
}

void BlueprintsMap::createBlueprint(const TileCoord mainTile, const BuildingType type, const char direction)
{
	std::cout << "create\n";
	map(mainTile) = Blueprint(type, direction);
	const uint8_t size = t1::bc::buildingsInfoTable.at(type).size;
	TileCoord tile;
	for (uint8_t i = 1; i < size; ++i)
	{
		tile = mainTile + t1::be::coordSquareArr[i];
		map(tile).type = BuildingType::AUXILARY;
	}
}

void BlueprintsMap::deleteBlueprint(const TileCoord mainTile)
{
	const uint8_t size = info(mainTile).size;
	TileCoord tile;
	for (uint8_t i = 0; i < size; ++i)
	{
		tile = mainTile + t1::be::coordSquareArr[i];
		map(tile).type = BuildingType::VOID_;
	}
}

void BlueprintsMap::placeBlueprint(const BuildingsMap& buildingsMap, const BuildingType type, const char direction, const TileCoord tile)
{
	if (!tileExists(tile))
		return;
	const bool remove = type == BuildingType::REMOVE;
	const bool build = buildingsMap.isAvaluablePlaceBuilding(type, tile, player);
	const bool plan = isAvaluablePlaceBlueprint(type, tile);
	const bool voidB = buildingsMap.isVoidBuilding(tile);
	if ((!remove && build && plan) || (remove && !voidB))
		createBlueprint(tile, type, direction);
	else if ((remove || !voidB) && isFilledTile(tile))
		deleteBlueprint(getMainTile(tile));
}

void BlueprintsMap::constructBuilding(BuildingsMap& buildingsMap, const TileCoord tile)
{
	if (!tileExists(tile))
		return;
	const TileCoord mainTile = getMainTile(tile);
	if (map(mainTile).type == BuildingType::REMOVE)
		buildingsMap.demolishBuilding(tile);
	else
		buildingsMap.constructBuilding(map(mainTile).type, map(mainTile).direction, mainTile, player);
	deleteBlueprint(mainTile);
}

BuildingType BlueprintsMap::getType(const TileCoord tile) const
{
	if (!tileExists(tile))
		return BuildingType::VOID_;
	return map(tile).type;
}


void BlueprintsMap::draw(sf::RenderWindow& window, const Camera& camera)
{
	using namespace sf::Literals;
	const TileCoord start = camera.getStartTile();
	const TileCoord end = camera.getEndTile();

	for (int x = start.x; x < end.x; ++x)
	{
		for (int y = start.y; y < end.y; ++y)
		{
			if (blueprintsMap[x][y].type == BuildingType::VOID_)
				continue;
			switch (blueprintsMap[x][y].direction)
			{
			case 'w': buildExample.setRotation(0_deg); break;
			case 'a': buildExample.setRotation(270_deg); break;
			case 's': buildExample.setRotation(180_deg); break;
			case 'd': buildExample.setRotation(90_deg); break;
			}
			buildExample.setTextureRect(info(TileCoord(x, y)).icoRect);
			buildExample.setPosition(sf::Vector2f(t1::be::pixelF(x), t1::be::pixelF(y)));
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
	buildExample.setOrigin(sf::Vector2f(_HALF_TILE_, _HALF_TILE_));
}
