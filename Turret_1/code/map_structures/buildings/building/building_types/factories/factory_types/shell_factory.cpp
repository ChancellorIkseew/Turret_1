
#include "shell_factory.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"


ShellFactory::ShellFactory(int v_type, short v_durability, short v_size, int tileX, int tileY) : Factory(v_type, v_durability, v_size, tileX, tileY)
{
	timer = 30;
}

ShellFactory::ShellFactory() : Factory()
{
	type = SHELL_FACTORY;
	timer = 30;
}

void ShellFactory::interact()
{
	--timer;

	if (timer == 0 || timer == 15)
	{
		placeResourceUnitX4(RES_AC_SHELLS);
	}

	if (timer == 0)
	{
		timer = 30;
		produceResource();
	}

	this->animation();
}


void ShellFactory::produceResource()
{
	if (isEnoughRes(RES_IRON, 1) && isEnoughRes(RES_SULFUR, 2) && !isEnoughRes(RES_AC_SHELLS, 20))
	{
		wasteResorce(RES_IRON, 1);
		wasteResorce(RES_SULFUR, 2);
		addToInventory(RES_AC_SHELLS, 1);
	}
}


bool ShellFactory::canAccept(int resType)
{
	if (resType == RES_IRON || resType == RES_SULFUR)
	{
		if (!isEnoughRes(resType, 20))
		return true;
	}
	return false;
}


void ShellFactory::animation()
{
	if (true)
	{

	}
}

void ShellFactory::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tileX * _TILE_, tileY * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 320, 64, 64));

	window.draw(buildingSprite);
}
