
#include "factory.h"


Factory::Factory(int type, short durability, short size, const TileCoord tile, Team* team) : Building(type, durability, size, tile, team)
{
	timer = 0;
}
