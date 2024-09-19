
#include "factory.h"
#include "../../../../resources/resource_units.h"
#include "../../../buildings_map.h"


Factory::Factory(int v_type, short v_durability, short v_size, int tileX, int tileY) : Building(v_type, v_durability, v_size, tileX, tileY)
{

}

Factory::Factory()
{

}


void Factory::interact()
{

	--timer;

	if (timer == 0 || timer == 15)
	{
		placeResourceUnit('0');
		//std::cout << "t place" << '\n';
	}

	if (timer == 0)
	{
		timer = 30;
		produceResource();
		//std::cout << "t mine" << '\n';
	}

	this->animation();
}



void Factory::placeResourceUnit(int type)
{

	for (int i = 0; i < size; ++i)
	{
		int tileX = this->tileX + coordSquareArr[i].x;
		int tileY = this->tileY + coordSquareArr[i].y;
		//std::cout << "try_coord:" << tileX << "_" << tileY << '\n';

		if (hasCorrectConveyerUp(tileX, tileY) && BuildingsMap::isThisPositionFree(tileX, tileY - 1, 2) && isEnoughRes(type, 1))
		{
			resourceUnitsList.emplace_back(new ResourceUnit(type, tileX * _TILE_ + _HALF_TILE_, tileY * _TILE_ - 6, 'w'));
			BuildingsMap::takePosition(tileX, tileY - 1, 2);
			wasteResorce(type, 1);
			//std::cout << "newRes_created" << '\n';
			return;
		}

		if (hasCorrectConveyerLeft(tileX, tileY) && BuildingsMap::isThisPositionFree(tileX - 1, tileY, 4) && isEnoughRes(type, 1))
		{
			resourceUnitsList.emplace_back(new ResourceUnit(type, tileX*_TILE_ - 6, tileY * _TILE_ + _HALF_TILE_, 'a'));
			BuildingsMap::takePosition(tileX - 1, tileY, 4);
			wasteResorce(type, 1);
			return;
		}

		if (hasCorrectConveyerDown(tileX, tileY) && BuildingsMap::isThisPositionFree(tileX, tileY + 1, 0) && isEnoughRes(type, 1))
		{
			resourceUnitsList.emplace_back(new ResourceUnit(type, tileX * _TILE_ + _HALF_TILE_, tileY * _TILE_ + 38, 's'));
			BuildingsMap::takePosition(tileX, tileY + 1, 0);
			wasteResorce(type, 1);
			return;
		}

		if (hasCorrectConveyerRight(tileX, tileY) && BuildingsMap::isThisPositionFree(tileX + 1, tileY, 3) && isEnoughRes(type, 1))
		{
			resourceUnitsList.emplace_back(new ResourceUnit(type, tileX * _TILE_ + 38, tileY * _TILE_ + _HALF_TILE_, 'd'));
			BuildingsMap::takePosition(tileX + 1, tileY, 3);
			wasteResorce(type, 1);
			return;
		}
	}
}
