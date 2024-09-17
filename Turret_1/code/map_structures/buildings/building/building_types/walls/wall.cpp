
#include "wall.h"
#include "../../buildings_enum.h"


StoneWall::StoneWall(char v_type, short v_durability, short v_size, int tileX, int tileY) : Building (v_type, v_durability, v_size, tileX, tileY)
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


StoneWall::~StoneWall()
{

}