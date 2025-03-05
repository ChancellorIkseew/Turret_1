
#include "damage.h"
#include "map_structures/world/world.h"

using namespace t1::be;

void Damage::createExplosion(const PixelCoord centrePixel, const int tileRadius, const float damage, const float dampingCoef, World& world)
{
	BuildingsMap& buildingsMap = world.getBuildingsMap();
	TileCoord centreTile = tile(centrePixel);
	TileCoord chekTile;
	for (int i = 0; i < tileRangeToSpiralRange[tileRadius]; ++i)
	{
		chekTile = centreTile + coordSpyralArr[i];
		if (buildingsMap.buildingExists(chekTile))
		{
			const float modifiedDamage = damage * world.getPreSettings().getShells().blastDamageModifier;
			buildingsMap.setDamage(modifiedDamage, chekTile);
		}
	}

	for (auto& [teamID, team] : world.getTeams())
	{
		for (auto& entity : team->getEneities().getList())
		{
			const PixelCoord delta = centrePixel - entity->getCoord();
			const float radius = pixel(tileRadius);
			if (pow2f(delta.x) + pow2f(delta.y) < pow2f(radius))
			{
				const float modifiedDamage = damage * world.getPreSettings().getShells().blastDamageModifier;
				entity->setDamage(modifiedDamage);
			}
		}
	}
}
