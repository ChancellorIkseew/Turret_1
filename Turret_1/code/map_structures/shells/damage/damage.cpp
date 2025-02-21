
#include "damage.h"
#include "map_structures/world/world.h"


void Damage::createExplosion(const PixelCoord centrePixel, const int tileRadius, const float damage, const float dampingCoef, World& world)
{
	BuildingsMap& buildingsMap = world.getBuildingsMap();
	TileCoord centreTile = t1::be::tile(centrePixel);
	TileCoord tile;
	for (int i = 0; i < t1::be::tileRangeToSpiralRange[tileRadius]; ++i)
	{
		tile = centreTile + t1::be::coordSpyralArr[i];
		if (buildingsMap.buildingExists(tile))
		{
			const float modifiedDamage = damage * world.getPreSettings().getShells().blastDamageModifier;
			buildingsMap.setDamage(modifiedDamage, tile);
		}
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
			{
				const float modifiedDamage = damage * world.getPreSettings().getShells().blastDamageModifier;
				entity->setDamage(modifiedDamage);
			}
		}
	}
}
