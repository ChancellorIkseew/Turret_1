
#include "stone_wall.h"
#include "map_structures/buildings/building/buildings_enum.h"


StoneWall::StoneWall(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building (durability, size, tile, team)
{

}


void StoneWall::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 448, 32, 32));

	window.draw(buildingSprite);
}
