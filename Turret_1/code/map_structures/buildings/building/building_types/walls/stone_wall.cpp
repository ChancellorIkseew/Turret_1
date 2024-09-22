
#include "stone_wall.h"
#include "map_structures/buildings/building/buildings_enum.h"


StoneWall::StoneWall(char type, short durability, short size, int tileX, int tileY) : Building (type, durability, size, tileX, tileY)
{

}

StoneWall::StoneWall() : Building()
{
	type = STONE_WALL;
}


void StoneWall::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tileX * _TILE_, tileY * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 448, 32, 32));

	window.draw(buildingSprite);
}
