
#include "big_drill.h"


BigDrill::BigDrill(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Drill(type, durability, size, tile, team)
{
	storageCapacity = 20;
}


void BigDrill::interact()
{
	if (timer % 15 == 0)
	{
		Building::placeResourceUnitX4(this->findResource());
	}

	if (timer == 0)
	{
		timer = 150;
		Drill::mineResource(2);
	}

	--timer;

	this->animation();
}

void BigDrill::animation()
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

void BigDrill::draw(sf::RenderWindow& window)
{
	buildingSprite.setOrigin(32, 32);
	buildingSprite.setRotation(rotorAngle);
	buildingSprite.setPosition(tile.x * _TILE_ + _TILE_, tile.y * _TILE_ + _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 32, 64, 64));

	window.draw(buildingSprite);

	buildingSprite.setOrigin(0, 0);
	buildingSprite.setRotation(0);
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(64, 32, 64, 64));

	window.draw(buildingSprite);
}
