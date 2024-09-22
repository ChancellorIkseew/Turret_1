
#include "factory.h"


Factory::Factory(int type, short durability, short size, int tileX, int tileY) : Building(type, durability, size, tileX, tileY)
{
	timer = 0;
}


bool Factory::isThisPositionFree(int position)
{
	return true;
}
