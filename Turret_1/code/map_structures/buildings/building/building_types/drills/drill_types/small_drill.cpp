
#include "small_drill.h"
#include "map_structures/buildings/building/buildings_enum.h"


SmallDrill::SmallDrill(int type, short durability, short size, int tileX, int tileY) : Drill(type, durability, size, tileX, tileY)
{

}

SmallDrill::SmallDrill()
{
	type = SMALL_DRILL;
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
	if (true)
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
	buildingSprite.setPosition(tileX * _TILE_ + _HALF_TILE_, tileY * _TILE_ + _HALF_TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	window.draw(buildingSprite);

	buildingSprite.setOrigin(0, 0);
	buildingSprite.setRotation(0);
	buildingSprite.setPosition(tileX * _TILE_, tileY * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));

	window.draw(buildingSprite);
}
