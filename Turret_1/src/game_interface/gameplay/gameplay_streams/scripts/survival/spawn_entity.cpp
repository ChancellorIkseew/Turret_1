
#include "spawn_entity.h"

#include "map_structures/team/team.h"
#include "t1_system/random/t1_random.h"


void randomMapBorderSpawn(const MobType type, Team& enemy, const TileCoord mapSize)
{
	const PixelCoord coord = randomMapBorderCoord(mapSize);
	enemy.spawnEntity(type, coord, Control::NONE);
}

PixelCoord randomMapBorderCoord(const TileCoord mapSize)
{
	TileCoord coord;
	const int side = t1::Rand::getValue(0, 3);
	switch (side)
	{
	case 0:
		coord.y = t1::Rand::getValue(0, mapSize.y - 1);
		break;
	case 1:
		coord.x =t1::Rand::getValue(0, mapSize.x - 1);
		break;
	case 2:
		coord.x = mapSize.x - 1;
		coord.y = t1::Rand::getValue(0, mapSize.y - 1);
		break;
	case 3:
		coord.x = t1::Rand::getValue(0, mapSize.x - 1);
		coord.y = mapSize.y - 1;
		break;
	}
	return t1::be::pixel(coord);
}