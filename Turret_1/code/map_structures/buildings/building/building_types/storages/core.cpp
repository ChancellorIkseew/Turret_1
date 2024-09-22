
#include "core.h"
#include "map_structures/buildings/building/buildings_enum.h"


Core::Core(int type, short durability, short size, int tileX, int tileY) : Building(type, durability, size, tileX, tileY)
{

}

Core::Core()
{
	type = CORE_MK1;
}


void Core::interact()
{

}


bool Core::isThisPositionFree(int position)
{
	return true;
}


bool Core::canAccept(int resType)
{
	return true;
}


void Core::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tileX * _TILE_, tileY * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 96, 128, 128));

	window.draw(buildingSprite);
}
