
#include "router.h"
#include "map_structures/buildings/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/resource_units.h"
#include "map_structures/resources/res_enum.h"


Router::Router(int type, short durability, short size, int tileX, int tileY) : Building(type, durability, size, tileX, tileY)
{

}

Router::Router() : Building()
{
	type = ROUTER;
}


void Router::interact()
{
	placeResourceUnitX1(RES_ANY_RES);
}


void Router::placeResourceUnitX1(int resType)
{
	short comonResQuant = 0;

	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		comonResQuant = comonResQuant + it->quant;
		if (it->quant > 0)
		{
			type = it->type;
			break;
		}
	}

	if (comonResQuant > 0)
	{
		Building::placeResourceUnitX1(type);
	}
}



bool Router::isThisPositionFree(int position) const
{
	short comonResQuant = 0;

	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		comonResQuant = comonResQuant + it->quant;

	}

	if (comonResQuant < 11)
	{
		return true;
	}
	return false;
}



bool Router::canAccept(int resType) const
{
	return true;
}


void Router::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tileX * _TILE_, tileY * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 256, 32, 32));
	window.draw(buildingSprite);
}
