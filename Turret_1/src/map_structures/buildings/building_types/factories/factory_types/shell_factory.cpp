
#include "shell_factory.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/world/world.h"


ShellFactory::ShellFactory(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Factory(durability, size, tile, team) { }


void ShellFactory::interact()
{
	if (timer <= 0 || timer == 15)
		placeResourceUnitX4(ResType::AC_SHELLS, world->getBuildingsMap());

	if (timer <= 0)
	{
		timer = 30;
		produceResource();
	}

	this->animation();
	--timer;
}


void ShellFactory::produceResource()
{
	if (isEnoughRes(ResType::IRON, 1) && isEnoughRes(ResType::SULFUR, 2) && !isEnoughRes(ResType::AC_SHELLS, 20))
	{
		wasteResorce(ResType::IRON, 1);
		wasteResorce(ResType::SULFUR, 2);
		addToInventory(ResType::AC_SHELLS, 1);
	}
}


bool ShellFactory::canAccept(const ResType resType) const
{
	if (resType != ResType::IRON && resType != ResType::SULFUR)
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
	buildingSprite.setPosition(sf::Vector2f(tile.x * _TILE_, tile.y * _TILE_));
	buildingSprite.setTextureRect(sf::IntRect({ 0, 320 }, X2_RECT));

	window.draw(buildingSprite);
}
