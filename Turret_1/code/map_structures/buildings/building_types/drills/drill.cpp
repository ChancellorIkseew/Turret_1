
#include "drill.h"
#include "map_structures/resources/res_enum.h"


Drill::Drill(int type, short durability, short size, const TileCoord tile, Team* team) : Building(type, durability, size, tile, team)
{
	timer = 0;
	rotorAngle = 0;
	storageCapacity = 0;
}


void Drill::mineResource(int amountFromOneTile)
{
	short size = Building::getSize();
	for (int i = 0; i < size; ++i)
	{
		int resType = TerrainMap::getTileType(tile.x + t1::be::coordSquareArr[i].x, tile.y + t1::be::coordSquareArr[i].y);

		if (resType != RES_NO_RESOURCES && !isStorageFull(storageCapacity))
		{
			addToInventory(resType, amountFromOneTile);
		}
	}
}
