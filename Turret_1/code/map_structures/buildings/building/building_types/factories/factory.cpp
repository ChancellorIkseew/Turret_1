
#include "factory.h"


Factory::Factory(int type, short durability, short size, const TileCoord tile) : Building(type, durability, size, tile)
{
	timer = 0;
}


bool Factory::isThisPositionFree(int position) const
{
	return true;
}
