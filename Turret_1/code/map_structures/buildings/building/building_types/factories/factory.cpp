
#include "factory.h"


Factory::Factory(int v_type, short v_durability, short v_size, int tileX, int tileY) : Building(v_type, v_durability, v_size, tileX, tileY)
{
	timer = 0;
}


bool Factory::isThisPositionFree(int position)
{
	return true;
}
