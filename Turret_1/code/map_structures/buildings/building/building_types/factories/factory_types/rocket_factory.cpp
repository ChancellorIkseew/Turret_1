
#include "rocket_factory.h"

#include "map_structures/resources/res_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"


RocketFactory::RocketFactory(int type, short durability, short size, int tileX, int tileY) : Factory(type, durability, size, tileX, tileY)
{
	timer = 120;
}


RocketFactory::RocketFactory() : Factory()
{
	type = ROCKET_FACTORY;
	timer = 120;
}


void RocketFactory::interact()
{
	--timer;

	if (timer%15 == 0)
	{
		placeResourceUnitX9(RES_ROCKET);
	}

	if (timer == 0)
	{
		timer = 120;
		produceResource();
	}

	this->animation();
}


void RocketFactory::produceResource()
{
	if (isEnoughRes(RES_IRON, 3) && isEnoughRes(RES_COPPER, 2) && isEnoughRes(RES_SILICON, 1) && isEnoughRes(RES_SULFUR, 10) && !isEnoughRes(RES_ROCKET, 60))
	{
		wasteResorce(RES_IRON, 3);
		wasteResorce(RES_COPPER, 2);
		wasteResorce(RES_SILICON, 1);
		wasteResorce(RES_SULFUR, 10);
		addToInventory(RES_ROCKET, 1);
	}
}


bool RocketFactory::canAccept(int resType)
{
	if (resType == RES_IRON || resType == RES_COPPER || resType == RES_SILICON || resType == RES_SULFUR)
	{
		if (!isEnoughRes(resType, 60))
			return true;
	}
	return false;
}


void RocketFactory::animation()
{
	if (true)
	{

	}
}

void RocketFactory::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tileX * _TILE_, tileY * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(256, 384, 96, 96));

	window.draw(buildingSprite);
}
