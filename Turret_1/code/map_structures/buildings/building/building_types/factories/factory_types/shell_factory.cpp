
#include <iostream>

#include "shell_factory.h"
#include "../../../../../resources/res_enum.h"
#include "../../../buildings_enum.h"
#include "../../../../../resources/res_enum.h"


ShellFactory::ShellFactory(int v_type, short v_durability, short v_size, int tileX, int tileY) : Factory(v_type, v_durability, v_size, tileX, tileY)
{
	timer = 30;
}


ShellFactory::ShellFactory() : Factory()
{
	type = SHELL_FACTORY;
	timer = 30;
	std::cout << "shell_factory_load" << '\n';
}


void ShellFactory::interact()
{

	--timer;

	if (timer == 0 || timer == 15)
	{
		placeResourceUnit(RES_AC_SHELLS);
		//std::cout << "t place" << '\n';
	}

	if (timer == 0)
	{
		timer = 30;
		produceResource();
		//std::cout << "t prod" << '\n';
	}

	this->animation();
}



void ShellFactory::produceResource()
{
	if (isEnoughRes(RES_IRON, 1) && isEnoughRes(RES_SULFUR, 2) && !isEnoughRes(RES_AC_SHELLS, 20))
	{
		//std::cout<< "amoo_created" << '\n';
		wasteResorce(RES_IRON, 1);
		wasteResorce(RES_SULFUR, 2);
		addToInventory(RES_AC_SHELLS, 1);
	}
}



void ShellFactory::animation()
{
	if (true)
	{

	}
}



bool ShellFactory::isThisPositionFree(int position)
{
	return true;
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



void ShellFactory::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tileX * _TILE_, tileY * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 320, 64, 64));

	window.draw(buildingSprite);
}



ShellFactory::~ShellFactory()
{
	storedResourcesList.clear();
}