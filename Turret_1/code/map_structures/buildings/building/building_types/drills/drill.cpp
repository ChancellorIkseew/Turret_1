
#include "drill.h"
#include "../../../../resources/resource_units.h"
#include "../../../../resources/res_enum.h"
#include "../../../buildings_map.h"


Drill::Drill(int v_type, short v_durability, short v_size, int tileX, int tileY) : Building(v_type, v_durability, v_size, tileX, tileY)
{
	timer = 30;
}

Drill::Drill()
{
	timer = 150;
}

Drill::~Drill()
{

}


void Drill::interact()
{
	if (timer % 15 == 0)
	{
		placeResourceUnit('X'); // this value does not mean anythings 
		// You can use any value. Notings will be changed.
	}

	if (timer == 0)
	{
		timer = 150;
		mineResource();
	}

	--timer;

	this->animation();
}



void Drill::mineResource()
{
	for (int i = 0; i < size; ++i)
	{
		int resType = TerrainMap::getTileType(tileX + coordSquareArr[i].x, tileY + coordSquareArr[i].y);

		if (resType != RES_NO_RESOURCES && !isEnoughRes(resType, 20))
		{
			addToInventory(resType, 1);
		}
	}
}



void Drill::placeResourceUnit(int type)
{
	for (int i = 0; i < size; ++i)
	{
		int tileX = this->tileX + coordSquareArr[i].x; 
		int tileY = this->tileY + coordSquareArr[i].y;

		int resType = this->findResource();

		if (resType != RES_NO_RESOURCES)
		{
			if (hasCorrectConveyerUp(tileX, tileY) && BuildingsMap::isThisPositionFree(tileX, tileY - 1, 2))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tileX * _TILE_ + _HALF_TILE_, tileY * _TILE_ - 6, 'w'));
				BuildingsMap::takePosition(tileX, tileY - 1, 2);
				wasteResorce(resType, 1);

				//std::cout << "newRes_created" << '\n';
				return;
			}

			if (hasCorrectConveyerLeft(tileX, tileY) && BuildingsMap::isThisPositionFree(tileX - 1, tileY, 4))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tileX * _TILE_ - 6, tileY * _TILE_ + _HALF_TILE_, 'a'));
				BuildingsMap::takePosition(tileX - 1, tileY, 4);
				wasteResorce(resType, 1);
				return;
			}

			if (hasCorrectConveyerDown(tileX, tileY) && BuildingsMap::isThisPositionFree(tileX, tileY + 1, 0))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tileX * _TILE_ + _HALF_TILE_, tileY * _TILE_ + 38, 's'));
				BuildingsMap::takePosition(tileX, tileY + 1, 0);
				wasteResorce(resType, 1);
				return;
			}

			if (hasCorrectConveyerRight(tileX, tileY) && BuildingsMap::isThisPositionFree(tileX + 1, tileY, 3))
			{
				resourceUnitsList.emplace_back(new ResourceUnit(resType, tileX * _TILE_ + 38, tileY * _TILE_ + _HALF_TILE_, 'd'));
				BuildingsMap::takePosition(tileX + 1, tileY, 3);
				wasteResorce(resType, 1);
				return;
			}
		}
	}
}
