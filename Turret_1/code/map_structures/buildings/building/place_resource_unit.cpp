
#include "building.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "t1_system/random/t1_random.h"


void Building::placeResourceUnit(const ResType resType, const TileCoord tile, BuildingsMap& buildingsMap)
{
	if (!isEnoughRes(resType, 1))
		return;

	int side = t1::Rand::getValue(0, 3);
	int i = 0;
	TileCoord cheekTile(0, 0);
	ResourceUnit unit;

	while (true)
	{
		switch (side)
		{
		case 0:
			if (++i > 4)
				return;
			cheekTile = TileCoord(tile.x, tile.y - 1);
			unit = ResourceUnit(resType, 'w', PixelCoord(0, 12));
			if (side == 0 && hasCorrectConveyerUp(tile, buildingsMap) &&
				buildingsMap.canAccept(unit, cheekTile) && isEnoughRes(resType, 1))
			{
				buildingsMap.addToInventory(unit, cheekTile);
				wasteResorce(resType, 1);
			}
			[[fallthrough]];
		case 1:
			if (++i > 4)
				return;
			cheekTile = TileCoord(tile.x - 1, tile.y);
			unit = ResourceUnit(resType, 'a', PixelCoord(12, 0));
			if (side == 1 && hasCorrectConveyerLeft(tile, buildingsMap) &&
				buildingsMap.canAccept(unit, cheekTile) && isEnoughRes(resType, 1))
			{
				buildingsMap.addToInventory(unit, cheekTile);
				wasteResorce(resType, 1);
			}
			[[fallthrough]];
		case 2:
			if (++i > 4)
				return;
			cheekTile = TileCoord(tile.x, tile.y + 1);
			unit = ResourceUnit(resType, 's', PixelCoord(0, -12));
			if (side == 2 && hasCorrectConveyerDown(tile, buildingsMap) &&
				buildingsMap.canAccept(unit, cheekTile) && isEnoughRes(resType, 1))
			{
				buildingsMap.addToInventory(unit, cheekTile);
				wasteResorce(resType, 1);
			}
			[[fallthrough]];
		case 3:
			if (++i > 4)
				return;
			cheekTile = TileCoord(tile.x + 1, tile.y);
			unit = ResourceUnit(resType, 'd', PixelCoord(-12, 0));
			if (side == 3 && hasCorrectConveyerRight(tile, buildingsMap) &&
				buildingsMap.canAccept(unit, cheekTile) && isEnoughRes(resType, 1))
			{
				buildingsMap.addToInventory(unit, cheekTile);
				wasteResorce(resType, 1);
			}
		}

		side = 0;
	}
}

void Building::placeResourceUnitX1(const ResType resType, BuildingsMap& buildingsMap)
{
	placeResourceUnit(resType, tile, buildingsMap);
}

void Building::placeResourceUnitX4(const ResType resType, BuildingsMap& buildingsMap)
{
	if (!isEnoughRes(resType, 1))
		return;
	for (int i = 0; i < 4; ++i)
	{
		TileCoord tryTile = tile + t1::be::coordSquareArr[i];
		placeResourceUnit(resType, tryTile, buildingsMap);
	}
}

void Building::placeResourceUnitX9(const ResType resType, BuildingsMap& buildingsMap)
{
	if (!isEnoughRes(resType, 1))
		return;
	for (int i = 0; i < 9; (i != 3 ? ++i : i += 2))
	{
		TileCoord tryTile = tile + t1::be::coordSquareArr[i];
		placeResourceUnit(resType, tryTile, buildingsMap);
	}
}