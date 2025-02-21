
#include "aiming.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/entities/entity/entity.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"
#include <iostream>

using namespace t1::be;

PixelCoord Aiming::aimForward(const Entity& entity, const World& world)
{
	const BuildingsMap& buildingsMap = world.getBuildingsMap();
	for (int i = 1; i <= entity.pixelRange; i++)
	{
		int tileX = tile(entity.coord.x + sin(entity.motionAngleRad) * _TILE_ * i);
		int tileY = tile(entity.coord.y + cos(entity.motionAngleRad) * _TILE_ * i);
		TileCoord tile(tileX, tileY);
		if (buildingsMap.buildingExists(tile) && buildingsMap.getTeamID(tile) != entity.team->getID())
			return pixel(tile);
	}
	return INCORRECT_PIXEL_COORD;
}


PixelCoord Aiming::aimOnBuilding(const Entity& entity, const BuildingsMap& buildingsMap)
{
	for (int i = 0; i < entity.spyralRange; i++)
	{
		TileCoord tile = entity.currentTile + coordSpyralArr[i];
		if (buildingsMap.buildingExists(tile) && buildingsMap.getTeamID(tile) != entity.team->getID())
			return pixel(tile);
	}
	return INCORRECT_PIXEL_COORD;
}


PixelCoord Aiming::aimOnEntity(const Entity& entity, const World& world)
{
	for (auto& team : world.getTeams())
	{
		if (entity.team->getID() != team.first)
		{
			auto& eList = team.second->getEneities().getList();
			for (auto& it : eList)
			{
				float deltaX = entity.coord.x - it->getCoord().x;
				float deltaY = entity.coord.y - it->getCoord().y;
				if (sqrt(deltaX * deltaX + deltaY * deltaY) < entity.pixelRange)
					return it->getCoord();
			}
		}
	}
	return INCORRECT_PIXEL_COORD;
}


PixelCoord Aiming::aimOnShell(const Entity& entity, const World& world)
{
	for (auto& team : world.getTeams())
	{
		if (entity.team->getID() != team.first)
		{
			for (auto& shell : team.second->getShells().getList())
			{
				if (shell->getType() == ShellType::ROCKET)
					return shell->getCoord();
			}
		}
	}
	return INCORRECT_PIXEL_COORD;
}
