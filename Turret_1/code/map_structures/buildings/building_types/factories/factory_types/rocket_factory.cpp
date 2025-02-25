
#include "rocket_factory.h"

#include "map_structures/resources/res_enum.h"
#include "map_structures/world/world.h"


RocketFactory::RocketFactory(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Factory(durability, size, tile, team) { }


void RocketFactory::interact()
{
	if (timer%15 == 0)
		placeResourceUnitX9(RES_ROCKET, world->getBuildingsMap());

	if (timer == 0)
	{
		timer = 120;
		produceResource();
	}

	this->animation();
	--timer;
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


bool RocketFactory::canAccept(const uint16_t resType) const
{
	if (resType != RES_IRON && resType != RES_COPPER && resType != RES_SILICON && resType != RES_SULFUR)
		return false;
	if (isEnoughRes(resType, 60))
		return false;
	return true;
}


void RocketFactory::animation()
{
	if (true)
	{

	}
}

void RocketFactory::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(256, 384, 96, 96));

	window.draw(buildingSprite);
}
