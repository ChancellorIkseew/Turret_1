
#include "core.h"


Core::Core(int type, short durability, short size, const TileCoord tile, Team* team) : Building(type, durability, size, tile, team)
{

}


void Core::interact()
{

}


bool Core::canAccept(const uint16_t resType) const
{
	return true;
}


void Core::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 96, 128, 128));

	window.draw(buildingSprite);
}
