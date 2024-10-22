
#include "core_mk2.h"


CoreMK2::CoreMK2(int type, short durability, short size, const TileCoord tile, Team* team) :
	Core(type, durability, size, tile, team)
{

}


void CoreMK2::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 96, 128, 128));

	window.draw(buildingSprite);
}
