
#include "drill.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/world/world.h"


Drill::Drill(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building(durability, size, tile, team) { }


void Drill::mineResource(const int amountFromOneTile, const int storageCapacity)
{
	short size = Building::getSize();
	for (int i = 0; i < size; ++i)
	{
		ResType resType = world->getTerrainMap().getTileType(tile + t1::be::coordSquareArr[i]);

		if (resType != ResType::NO_RESOURCES && !isStorageFull(storageCapacity))
		{
			addToInventory(resType, amountFromOneTile);
		}
	}
}
