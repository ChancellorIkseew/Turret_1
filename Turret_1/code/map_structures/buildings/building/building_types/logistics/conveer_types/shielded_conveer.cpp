
#include "shielded_conveer.h"
#include "../../../buildings_enum.h"


ShieldedConveyer::ShieldedConveyer(char v_type, char v_direction, short v_durability, short v_size, int tileX, int tileY) : Conveyer(v_type, v_direction, v_durability, v_size, tileX, tileY)
{
	for (int i = 0; i < 5; ++i)
	{
		isPositionFree[i] = true;
	}
}

ShieldedConveyer::ShieldedConveyer() : Conveyer()
{
	type = SHIELDED_CONVEYER_DOWN;

	for (int i = 0; i < 5; ++i)
	{
		isPositionFree[i] = true;
	}
}

ShieldedConveyer::~ShieldedConveyer()
{

}

void ShieldedConveyer::load(std::ifstream& fin)
{
	fin >> size >> durability >> tileX >> tileY >> direction;

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
}


void ShieldedConveyer::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tileX * _TILE_ + _HALF_TILE_, tileY * _TILE_ + _HALF_TILE_);
	
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
