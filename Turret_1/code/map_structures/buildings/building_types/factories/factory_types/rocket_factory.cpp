
#include "rocket_factory.h"

#include "map_structures/resources/res_enum.h"
#include "map_structures/world/world.h"


RocketFactory::RocketFactory(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Factory(durability, size, tile, team) { }


void RocketFactory::interact()
{
	if (timer%15 == 0)
		placeResourceUnitX9(ResType::ROCKET, world->getBuildingsMap());

	if (timer <= 0)
	{
		timer = 120;
		produceResource();
	}

	this->animation();
	--timer;
}


void RocketFactory::produceResource()
{
	if (isEnoughRes(ResType::IRON, 3) && isEnoughRes(ResType::COPPER, 2) && isEnoughRes(ResType::SILICON, 1) && isEnoughRes(ResType::SULFUR, 10) && !isEnoughRes(ResType::ROCKET, 60))
	{
		wasteResorce(ResType::IRON, 3);
		wasteResorce(ResType::COPPER, 2);
		wasteResorce(ResType::SILICON, 1);
		wasteResorce(ResType::SULFUR, 10);
		addToInventory(ResType::ROCKET, 1);
	}
}


bool RocketFactory::canAccept(const ResType resType) const
{
	if (resType != ResType::IRON && resType != ResType::COPPER && resType != ResType::SILICON && resType != ResType::SULFUR)
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
