
#include "stone_tower.h"
#include "map_structures/buildings/building/buildings_enum.h"


StoneTower::StoneTower(char type, short durability, short size, const TileCoord tile) : Tower (type, durability, size, tile)
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
