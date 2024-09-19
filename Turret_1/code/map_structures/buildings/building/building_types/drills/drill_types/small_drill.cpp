
#include "small_drill.h"
#include "../../../buildings_enum.h"


SmallDrill::SmallDrill(int v_type, short v_durability, short v_size, int tileX, int tileY) : Drill(v_type, v_durability, v_size, tileX, tileY)
{

}



SmallDrill::SmallDrill()
{
	type = SMALL_DRILL;
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

	//std::cout << "draw_drill" << '\n';
	//std::cout << "draw_drill" << '\n';
}
