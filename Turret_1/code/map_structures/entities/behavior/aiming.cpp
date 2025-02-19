
#include "aiming.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/entities/entity/entity.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"

using namespace t1::be;

PixelCoord t1::ent::findAim(const Entity& entity, const World& world)
{
	/*
	for (auto& team : world.getTeams())
	{
		if (entity.team->getID() != team.first)
		{
			for (auto en = team.second->entities.begin(); en != team.second->entities.end(); ++en)
			{
				float deltaX = entity.coord.x - (*en)->getCoord().x;
				float deltaY = entity.coord.y - (*en)->getCoord().y;

				if (sqrt(deltaX * deltaX + deltaY * deltaY) < entity.pixelRange)
				{
					return (*en)->getCoord();
				}
			}
		}
	}
	*/

	BuildingsMap buildingsMap = world.getBuildingsMap();

	for (int i = 1; i <= entity.pixelRange; i++)
	{
		int tileX = tile(entity.coord.x + sin(entity.motionAngleRad) * _TILE_ * i);
		int tileY = tile(entity.coord.y + cos(entity.motionAngleRad) * _TILE_ * i);
		TileCoord tile{ tileX, tileY };
		if (buildingsMap.buildingExists(tile) && buildingsMap.getTeamID(tile) != entity.team->getID())
		{
			return pixel(tile);
		}
	}

	for (int i = 0; i < entity.spyralRange; i++)
	{
		int tileX = entity.currentTile.x + coordSpyralArr[i].x;
		int tileY = entity.currentTile.y + coordSpyralArr[i].y;
		TileCoord tile{ tileX, tileY };
		if (buildingsMap.buildingExists(tile) && buildingsMap.getTeamID(tile) != entity.team->getID())
		{
			return pixel(tile);
		}
	}

	return { 0.0f, 0.0f };
}
