#include "big_drill.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/res_enum.h"


BigDrill::BigDrill(int v_type, short v_durability, short v_size, int tileX, int tileY) : Drill(v_type, v_durability, v_size, tileX, tileY)
{
	
}

BigDrill::BigDrill() : Drill()
{
	type = BIG_DRILL;
}




void BigDrill::mineResource()
{
	for (int i = 0; i < size; ++i)
	{
		int resType = TerrainMap::getTileType(tileX + coordSquareArr[i].x, tileY + coordSquareArr[i].y);

		if (resType != RES_NO_RESOURCES && !isEnoughRes(resType, 20))
		{
			addToInventory(resType, 2);
		}
	}
}



void BigDrill::animation()
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


void BigDrill::draw(sf::RenderWindow& window)
{
	buildingSprite.setOrigin(32, 32);
	buildingSprite.setRotation(rotorAngle);
	buildingSprite.setPosition(tileX * _TILE_ + _TILE_, tileY * _TILE_ + _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 32, 64, 64));

	window.draw(buildingSprite);

	buildingSprite.setOrigin(0, 0);
	buildingSprite.setRotation(0);
	buildingSprite.setPosition(tileX * _TILE_, tileY * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(64, 32, 64, 64));

	window.draw(buildingSprite);
	//std::cout << "draw_drill" << '\n';
	//std::cout << "draw_drill" << '\n';
}
