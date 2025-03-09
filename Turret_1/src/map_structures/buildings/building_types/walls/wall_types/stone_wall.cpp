
#include "stone_wall.h"

StoneWall::StoneWall(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building (durability, size, tile, team) { }

void StoneWall::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(sf::Vector2f(tile.x * _TILE_, tile.y * _TILE_));
	buildingSprite.setTextureRect(sf::IntRect({ 0, 448 }, X1_RECT));

	window.draw(buildingSprite);
}
