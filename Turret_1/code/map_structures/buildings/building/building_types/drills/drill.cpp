
#include "drill.h"
#include "map_structures/resources/res_enum.h"


Drill::Drill(int type, short durability, short size, const TileCoord tile) : Building(type, durability, size, tile)

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
		int resType = TerrainMap::getTileType(tile.x + coordSquareArr[i].x, tile.y + coordSquareArr[i].y);

		if (resType != RES_NO_RESOURCES && !isEnoughRes(resType, 20))
		{
			addToInventory(resType, amountFromOneTile);
		}
	}
}
