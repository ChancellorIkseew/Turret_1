
#include "standard_conveyer.h"


StandardConveyer::StandardConveyer(char type, char direction, short durability, short size, const TileCoord tile, Team* team) : 
	Conveyer(type, direction, durability, size, tile, team)
{
	speed = 2.0f;
}

void StandardConveyer::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_ + _HALF_TILE_, tile.y * _TILE_ + _HALF_TILE_);

	buildingSprite.setTextureRect(sf::IntRect(128, 96, 32, 32));
	buildingSprite.setOrigin(16, 16);

	switch (direction)
	{
	case 'a':
		buildingSprite.setRotation(270);
		break;

	case 's':
		buildingSprite.setRotation(180);
		break;

	case 'd':
		buildingSprite.setRotation(90);
		break;
	}

	window.draw(buildingSprite);

	buildingSprite.setRotation(0);
	buildingSprite.setOrigin(0, 0);

	for (auto& res : resUnits)
		res.draw(window, tile);
}