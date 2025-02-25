
#include "shell_factory.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/world/world.h"


ShellFactory::ShellFactory(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Factory(durability, size, tile, team) { }


void ShellFactory::interact()
{
	if (timer == 0 || timer == 15)
		placeResourceUnitX4(RES_AC_SHELLS, world->getBuildingsMap());

	if (timer == 0)
	{
		timer = 30;
		produceResource();
	}

	this->animation();
	--timer;
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


bool ShellFactory::canAccept(const uint16_t resType) const
{
	if (resType != RES_IRON && resType != RES_SULFUR)
		return false;
	if (isEnoughRes(resType, 20))
		return false;
	return true;
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
