
#include "rocket_factory.h"
#include "../../../../../resources/res_enum.h"
#include "../../../buildings_enum.h"


RocketFactory::RocketFactory(int v_type, short v_durability, short v_size, int tileX, int tileY) : Factory(v_type, v_durability, v_size, tileX, tileY)
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
		placeResourceUnit(RES_ROCKET);
		//std::cout << "t place" << '\n';
	}

	if (timer == 0)
	{
		timer = 120;
		produceResource();
		//std::cout << "t prod" << '\n';
	}

	this->animation();
}




void RocketFactory::produceResource()
{
	if (isEnoughRes(RES_IRON, 3) && isEnoughRes(RES_COPPER, 2) && isEnoughRes(RES_SILICON, 1) && isEnoughRes(RES_SULFUR, 10) && !isEnoughRes(RES_ROCKET, 60))
	{
		//std::cout<< "rocket_created" << '\n';
		wasteResorce(RES_IRON, 3);
		wasteResorce(RES_COPPER, 2);
		wasteResorce(RES_SILICON, 1);
		wasteResorce(RES_SULFUR, 10);
		addToInventory(RES_ROCKET, 1);
	}
}





void RocketFactory::animation()
{
	if (true)
	{

	}
}



bool RocketFactory::isThisPositionFree(int position)
{
	return true;
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



void RocketFactory::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tileX * _TILE_, tileY * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(256, 384, 96, 96));

	window.draw(buildingSprite);
}



RocketFactory::~RocketFactory()
{
	storedResourcesList.clear();
}