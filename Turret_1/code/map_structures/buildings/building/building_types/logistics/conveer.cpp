
#include "conveer.h"
#include "../../buildings_enum.h"


Conveyer::Conveyer(char v_type, char v_direction, short v_durability, short v_size, int tileX, int tileY) : Building(v_type, v_durability, v_size, tileX, tileY)
{
	direction = v_direction;

	for (int i = 0; i < 5; ++i)
	{
		isPositionFree[i] = true;
	}
}

Conveyer::Conveyer() : Building()
{
	type = STANDARD_CONVEYER_DOWN;

	for (int i = 0; i < 5; ++i)
	{
		isPositionFree[i] = true;
	}
}


void Conveyer::save(std::ofstream& fout)
{
	fout << type << " " << size << " " << durability <<
		" " << tileX << " " << tileY << " " << direction << '\n';

	fout << "$\n";
}


void Conveyer::load(std::ifstream& fin)
{
	fin >> size >> durability >> tileX >> tileY >> direction;

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

	char specialSymbol;
	fin >> specialSymbol;
}



void Conveyer::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tileX * _TILE_ + _HALF_TILE_, tileY * _TILE_ + _HALF_TILE_);
	
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



bool Conveyer::isThisPositionFree(int position)
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

bool Conveyer::canAccept(int resType)
{
	return true;
}