
#include "stone_tower.h"

StoneTower::StoneTower(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Tower(durability, size, tile, team) {}

void StoneTower::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(sf::Vector2f(tile.x * _TILE_, tile.y * _TILE_));
	buildingSprite.setTextureRect(sf::IntRect({ 0, 416 }, X1_RECT));

	window.draw(buildingSprite);
	if (turret != nullptr)
	{
		turret->draw(window);
	}
}
