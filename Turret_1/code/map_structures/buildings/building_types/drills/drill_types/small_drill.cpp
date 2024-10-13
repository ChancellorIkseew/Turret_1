
#include "small_drill.h"


SmallDrill::SmallDrill(int type, short durability, short size, const TileCoord tile, Team* team) : Drill(type, durability, size, tile, team)
{
	storageCapacity = 5;
}


void SmallDrill::interact()
{
	if (timer % 15 == 0)
	{
		Building::placeResourceUnitX1(this->findResource());
	}

	if (timer == 0)
	{
		timer = 150;
		Drill::mineResource(1);
	}

	--timer;

	this->animation();
}


void SmallDrill::animation()
{
	if (!isStorageFull(storageCapacity))
	{
		rotorAngle += 0.5;
		if (rotorAngle >= 360)
		{
			rotorAngle -= 360;
		}
	}
}

void SmallDrill::draw(sf::RenderWindow& window)
{
	buildingSprite.setOrigin(16, 16);
	buildingSprite.setRotation(rotorAngle);
	buildingSprite.setPosition(tile.x * _TILE_ + _HALF_TILE_, tile.y * _TILE_ + _HALF_TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	window.draw(buildingSprite);

	buildingSprite.setOrigin(0, 0);
	buildingSprite.setRotation(0);
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));

	window.draw(buildingSprite);
}
