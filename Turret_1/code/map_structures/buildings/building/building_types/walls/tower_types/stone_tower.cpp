
#include "stone_tower.h"
#include "map_structures/buildings/building/buildings_enum.h"


StoneTower::StoneTower(char v_type, short v_durability, short v_size, int tileX, int tileY) : Tower (v_type, v_durability, v_size, tileX, tileY)
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
