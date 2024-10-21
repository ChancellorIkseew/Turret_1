
#include "stone_wall.h"
#include "map_structures/buildings/building/buildings_enum.h"


StoneWall::StoneWall(char type, short durability, short size, const TileCoord tile, Team* team) : Building (type, durability, size, tile, team)
{

}


void StoneWall::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 448, 32, 32));

	window.draw(buildingSprite);
}
