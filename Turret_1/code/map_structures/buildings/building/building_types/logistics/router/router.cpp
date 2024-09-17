
#include "router.h"

#include "../../../../buildings_map.h"
#include "../../../buildings_enum.h"
#include "../../../../../resources/resource_units.h"


Router::Router(int v_type, short v_durability, short v_size, int tileX, int tileY) : Building(v_type, v_durability, v_size, tileX, tileY)
{

}

Router::Router() : Building()
{
	type = ROUTER;
}


void Router::interact()
{
	placeResourceUnit('X');
}


void Router::placeResourceUnit(int type)
{
	short comonResQuant = 0;

	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		comonResQuant = comonResQuant + it->quant;
		if (it->quant != 0)
			type = it->type;
	}

	if(comonResQuant > 0 &&((hasCorrectConveyerUp(tileX, tileY) &&
		BuildingsMap::isThisPositionFree(tileX, tileY - 1, 2)) ||
		(hasCorrectConveyerLeft(tileX, tileY) &&
		BuildingsMap::isThisPositionFree(tileX - 1, tileY, 4)) ||
		(hasCorrectConveyerDown(tileX, tileY) &&
		BuildingsMap::isThisPositionFree(tileX, tileY + 1, 0)) ||
		(hasCorrectConveyerRight(tileX, tileY) &&
		BuildingsMap::isThisPositionFree(tileX + 1, tileY, 3))
		))
	while (true)
	{
		int side = rand() % 4;
		//std::cout << "try_coord:" << tileX << "_" << tileY << '\n';

		if (side == 0 && hasCorrectConveyerUp(tileX, tileY) && 
			BuildingsMap::isThisPositionFree(tileX, tileY - 1, 2) && isEnoughRes(type, 1))
		{
			resourceUnitsList.emplace_back(new ResourceUnit(type, tileX * _TILE_ + _HALF_TILE_, tileY * _TILE_ - 6, 'w'));
			BuildingsMap::takePosition(tileX, tileY - 1, 2);
			wasteResorce(type, 1);
			//std::cout << "newRes_created" << '\n';
			return;
		}

		if (side == 1 && hasCorrectConveyerLeft(tileX, tileY) && 
			BuildingsMap::isThisPositionFree(tileX - 1, tileY, 4) && isEnoughRes(type, 1))
		{
			resourceUnitsList.emplace_back(new ResourceUnit(type, tileX * _TILE_ - 6, tileY * _TILE_ + _HALF_TILE_, 'a'));
			BuildingsMap::takePosition(tileX - 1, tileY, 4);
			wasteResorce(type, 1);
			return;
		}

		if (side == 2 && hasCorrectConveyerDown(tileX, tileY) && 
			BuildingsMap::isThisPositionFree(tileX, tileY + 1, 0) && isEnoughRes(type, 1))
		{
			resourceUnitsList.emplace_back(new ResourceUnit(type, tileX * _TILE_ + _HALF_TILE_, tileY * _TILE_ + 38, 's'));
			BuildingsMap::takePosition(tileX, tileY + 1, 0);
			wasteResorce(type, 1);
			return;
		}

		if (side == 3 && hasCorrectConveyerRight(tileX, tileY) && 
			BuildingsMap::isThisPositionFree(tileX + 1, tileY, 3) && isEnoughRes(type, 1))
		{
			resourceUnitsList.emplace_back(new ResourceUnit(type, tileX * _TILE_ + 38, tileY * _TILE_ + _HALF_TILE_, 'd'));
			BuildingsMap::takePosition(tileX + 1, tileY, 3);
			wasteResorce(type, 1);
			return;
		}
	}
}



bool Router::isThisPositionFree(int position)
{
	short comonResQuant = 0;

	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		comonResQuant = comonResQuant + it->quant;

	}

	if (comonResQuant < 11)
	{
		return true;
	}
	return false;
}



bool Router::canAccept(int resType)
{
	return true;
}


void Router::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tileX * _TILE_, tileY * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 256, 32, 32));
	window.draw(buildingSprite);
}


Router::~Router()
{

}
