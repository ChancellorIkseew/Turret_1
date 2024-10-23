
#include "stone_tower.h"
#include "map_structures/buildings/building/buildings_enum.h"


StoneTower::StoneTower(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Tower (type, durability, size, tile, team)
{

}


void StoneTower::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 416, 32, 32));

	window.draw(buildingSprite);
	if (turret != nullptr)
	{
		turret->draw(window);
	}
}
