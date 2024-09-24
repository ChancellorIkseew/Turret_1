
#include "shielded_conveer.h"
#include "map_structures/buildings/building/buildings_enum.h"


ShieldedConveyer::ShieldedConveyer(char type, char direction, short durability, short size, const TileCoord tile) : Conveyer(type, direction, durability, size, tile)
{
	this->direction = direction;

	for (int i = 0; i < 5; ++i)
	{
		isPositionFree[i] = true;
	}
}


void ShieldedConveyer::load(std::ifstream& fin)
{
	fin >> direction;

	switch (direction)
	{
	case 'w':
		type = SHIELDED_CONVEYER_UP;
		break;

	case 'a':
		type = SHIELDED_CONVEYER_LEFT;
		break;

	case 's':
		type = SHIELDED_CONVEYER_DOWN;
		break;

	case 'd':
		type = SHIELDED_CONVEYER_RIGHT;
		break;
	}

	Building::load(fin);
}


void ShieldedConveyer::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_ + _HALF_TILE_, tile.y * _TILE_ + _HALF_TILE_);
	
	buildingSprite.setTextureRect(sf::IntRect(160, 96, 32, 32));
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
}
