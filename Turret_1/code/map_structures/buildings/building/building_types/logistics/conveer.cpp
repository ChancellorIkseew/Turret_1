
#include "conveer.h"
#include "map_structures/buildings/building/buildings_enum.h"


Conveyer::Conveyer(char type, char direction, short durability, short size, const TileCoord tile) : Building(type, durability, size, tile)
{
	this->direction = direction;

	for (int i = 0; i < 5; ++i)
	{
		isPositionFree[i] = true;
	}
}


void Conveyer::save(std::ofstream& fout) const
{
	fout << direction << '\n';
	Building::save(fout);
}

void Conveyer::load(std::ifstream& fin)
{
	fin >> direction;

	switch (direction)
	{
	case 'w':
		type = STANDARD_CONVEYER_UP;
		break;

	case 'a':
		type = STANDARD_CONVEYER_LEFT;
		break;

	case 's':
		type = STANDARD_CONVEYER_DOWN;
		break;

	case 'd':
		type = STANDARD_CONVEYER_RIGHT;
		break;
	}

	Building::load(fin);
}



void Conveyer::draw(sf::RenderWindow& window)
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
}



bool Conveyer::isThisPositionFree(int position) const
{
	return isPositionFree[position];
}

void Conveyer::takePosition(int position)
{
	isPositionFree[position] = false;
}

void Conveyer::leavePosition(int position)
{
	isPositionFree[position] = true;
}

bool Conveyer::canAccept(int resType) const
{
	return true;
}
