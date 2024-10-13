
#include "shell_factory.h"

#include "map_structures/resources/res_enum.h"


ShellFactory::ShellFactory(int type, short durability, short size, const TileCoord tile, Team* team) : Factory(type, durability, size, tile, team)
{
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


bool ShellFactory::canAccept(const int resType) const
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
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 320, 64, 64));

	window.draw(buildingSprite);
}
