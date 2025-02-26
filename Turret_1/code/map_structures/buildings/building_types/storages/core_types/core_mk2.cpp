
#include "core_mk2.h"


CoreMK2::CoreMK2(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Core(durability, size, tile, team) { }

void CoreMK2::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 96, 128, 128));

	window.draw(buildingSprite);
}
