
#include "router.h"
#include "map_structures/buildings/buildings_map.h"
#include "map_structures/resources/resource_units.h"
#include "map_structures/resources/res_enum.h"


Router::Router(int type, short durability, short size, const TileCoord tile) : Building(type, durability, size, tile)
{

}


void Router::interact()
{
	int resType = findResource();
	if (resType != RES_NO_RESOURCES)
	{
		placeResourceUnitX1(resType);
	}
}


bool Router::isThisPositionFree(int position) const
{
	short comonResQuant = 0;

	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		comonResQuant = comonResQuant + it->quant;
	}

	if (comonResQuant < 11)
	{
		return true;
	}
	return false;
}


bool Router::canAccept(int resType) const
{
	return true;
}


void Router::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 256, 32, 32));
	window.draw(buildingSprite);
}
