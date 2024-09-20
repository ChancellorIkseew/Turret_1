
#include "drill.h"
#include "map_structures/resources/res_enum.h"


Drill::Drill(int v_type, short v_durability, short v_size, int tileX, int tileY) : Building(v_type, v_durability, v_size, tileX, tileY)
{
	timer = 0;
	rotorAngle = 0;
}

Drill::Drill()
{
	timer = 0;
	rotorAngle = 0;
}


void Drill::mineResource(int amountFromOneTile)
{
	for (int i = 0; i < size; ++i)
	{
		int resType = TerrainMap::getTileType(tileX + coordSquareArr[i].x, tileY + coordSquareArr[i].y);

		if (resType != RES_NO_RESOURCES && !isEnoughRes(resType, 20))
		{
			addToInventory(resType, amountFromOneTile);
		}
	}
}
