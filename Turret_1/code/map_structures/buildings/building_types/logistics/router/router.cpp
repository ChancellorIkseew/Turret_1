
#include "router.h"
#include "map_structures/resources/res_enum.h"


Router::Router(int type, short durability, short size, const TileCoord tile, Team* team) : Building(type, durability, size, tile, team)
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


bool Router::canAccept(const uint16_t resType) const
{
	if (Building::isStorageFull(10))
		return false;
	return true;
}


void Router::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 256, 32, 32));
	window.draw(buildingSprite);
}
