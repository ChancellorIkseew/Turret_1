
#include "intersection.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/world/world.h"

constexpr int STORAGE_CAPACITY = 10;

Intersection::Intersection(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building(durability, size, tile, team) { }


void Intersection::interact()
{
	if (--timer > 0)
		return;
	timer = 5;
	placeUnit();
}


void Intersection::placeUnit()
{
	BuildingsMap& buildingsMap = world->getBuildingsMap();
	for (auto& res : resUnits)
	{
		TileCoord checkTile;
		ResType resType = res.type;
		ResourceUnit unit;

		switch (res.direction)
		{
		case 'w':
			checkTile = TileCoord(tile.x, tile.y - 1);
			unit = ResourceUnit(resType, 'w', PixelCoord(0, 12));
			if (res.direction == 'w' && hasCorrectConveyerUp(tile, buildingsMap) &&
				buildingsMap.canAccept(unit, checkTile) && isEnoughRes(resType, 1))
			{
				buildingsMap.addToInventory(unit, checkTile);
				wasteResorce(resType, 1);
			}
			break;
		case 'a':
			checkTile = TileCoord(tile.x - 1, tile.y);
			unit = ResourceUnit(resType, 'a', PixelCoord(12, 0));
			if (res.direction == 'a' && hasCorrectConveyerLeft(tile, buildingsMap) &&
				buildingsMap.canAccept(unit, checkTile) && isEnoughRes(resType, 1))
			{
				buildingsMap.addToInventory(unit, checkTile);
				wasteResorce(resType, 1);
			}
			break;
		case 's':
			checkTile = TileCoord(tile.x, tile.y + 1);
			unit = ResourceUnit(resType, 's', PixelCoord(0, -12));
			if (res.direction == 's' && hasCorrectConveyerDown(tile, buildingsMap) &&
				buildingsMap.canAccept(unit, checkTile) && isEnoughRes(resType, 1))
			{
				buildingsMap.addToInventory(unit, checkTile);
				wasteResorce(resType, 1);
			}
			break;
		case 'd':
			checkTile = TileCoord(tile.x + 1, tile.y);
			unit = ResourceUnit(resType, 'd', PixelCoord(-12, 0));
			if (res.direction == 'd' && hasCorrectConveyerRight(tile, buildingsMap) &&
				buildingsMap.canAccept(unit, checkTile) && isEnoughRes(resType, 1))
			{
				buildingsMap.addToInventory(unit, checkTile);
				wasteResorce(resType, 1);
			}
			break;
		}
	}
}


bool Intersection::canAccept(const ResType resType) const
{
	return resUnits.size() < STORAGE_CAPACITY;
}

void Intersection::addToInventory(ResourceUnit& unit)
{
	resUnits.emplace_back(std::move(unit));
}


void Intersection::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(32, 256, 32, 32));
	window.draw(buildingSprite);
}
