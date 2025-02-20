
#include "damage.h"
#include "map_structures/world/world.h"
#include <iostream>


void Damage::createBurst(const PixelCoord centrePixel, const int tileRadius, const uint16_t damage, const float dampingCoef, World& world)
{
	BuildingsMap& buildingsMap = world.getBuildingsMap();
	TileCoord centreTile = t1::be::tile(centrePixel);
	TileCoord tile;
	for (int i = 0; i < t1::be::tileRangeToSpiralRange[tileRadius]; ++i)
	{
		tile = centreTile + t1::be::coordSpyralArr[i];
		if (buildingsMap.buildingExists(tile))
			buildingsMap.setDamage(damage, tile);
	}

	for (auto& it : world.getTeams())
	{
		Team& team = *it.second;
		for (auto& entity : team.getEneities().getList())
		{
			float deltaX = centrePixel.x - entity->getCoord().x;
			float deltaY = centrePixel.y - entity->getCoord().y;
			float deltaS = sqrt(deltaX * deltaX + deltaY * deltaY);
			if (deltaS < t1::be::pixel(tileRadius))
				entity->setDamage(damage);
		}
	}
}
