
#include "stone_tower.h"
#include "map_structures/buildings/building/buildings_enum.h"


StoneTower::StoneTower(char type, short durability, short size, int tileX, int tileY) : Tower (type, durability, size, tileX, tileY)
{

}


StoneTower::StoneTower() : Tower()
{
	type = STONE_TOWER;
}


void StoneTower::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tileX * _TILE_, tileY * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 416, 32, 32));

	window.draw(buildingSprite);
	if (turret != nullptr)
	{
		turret->draw(window);
	}
}
