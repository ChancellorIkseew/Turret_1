
#include "core.h"
#include "map_structures/buildings/building/buildings_enum.h"


Core::Core(int type, short durability, short size, const TileCoord tile) : Building(type, durability, size, tile)
{

}


void Core::interact()
{

}


bool Core::isThisPositionFree(int position) const
{
	return true;
}


bool Core::canAccept(int resType) const
{
	return true;
}


void Core::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 96, 128, 128));

	window.draw(buildingSprite);
}
