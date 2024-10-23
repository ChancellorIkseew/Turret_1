
#include "factory.h"


Factory::Factory(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building(type, durability, size, tile, team)
{
	timer = 0;
}
