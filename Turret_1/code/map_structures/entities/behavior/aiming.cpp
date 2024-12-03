
#include "aiming.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/entities/entity/entity.h"
#include "map_structures/team/team.h"

using namespace t1::be;

PixelCoord t1::ent::findAim(const Entity& entity)
{
	for (auto& tm : Team::teams)
	{
		if (entity.team->getID() != tm->getID())
		{
			for (auto en = tm->entities.begin(); en != tm->entities.end(); ++en)
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

	for (int i = 1; i <= entity.pixelRange; i++)
	{
		int tileX = tile(entity.coord.x + sin(entity.motionAngleRad) * _TILE_ * i);
		int tileY = tile(entity.coord.y + cos(entity.motionAngleRad) * _TILE_ * i);
		TileCoord tile{ tileX, tileY };
		if (BuildingsMap::buildingExists(tile) && BuildingsMap::getTeamID(tile) != entity.team->getID())
		{
			return pixel(tile);
		}
	}

	for (int i = 0; i < entity.spyralRange; i++)
	{
		int tileX = entity.currentTile.x + coordSpyralArr[i].x;
		int tileY = entity.currentTile.y + coordSpyralArr[i].y;
		TileCoord tile{ tileX, tileY };
		if (BuildingsMap::buildingExists(tile) && BuildingsMap::getTeamID(tile) != entity.team->getID())
		{
			return pixel(tile);
		}
	}

	return { 0.0f, 0.0f };
}
