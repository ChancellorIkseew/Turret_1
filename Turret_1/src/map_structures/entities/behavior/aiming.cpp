
#include "aiming.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/entities/entity/entity.h"
#include "map_structures/entities/turret/turret.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"
#include <iostream>

using namespace t1::be;

PixelCoord Aiming::aimForward(const Entity& entity, const int tileRange, const World& world)
{
	const BuildingsMap& buildingsMap = world.getBuildingsMap();
	for (int i = 1; i <= tileRange; i++)
	{
		int tileX = tile(entity.coord.x + sin(entity.motionAngleRad) * _TILE_ * i);
		int tileY = tile(entity.coord.y + cos(entity.motionAngleRad) * _TILE_ * i);
		TileCoord tile(tileX, tileY);
		if (buildingsMap.buildingExists(tile) && buildingsMap.getTeamID(tile) != entity.team->getID())
			return pixel(tile);
	}
	return INCORRECT_PIXEL_COORD;
}


PixelCoord Aiming::aimOnBuilding(const Entity& entity, const int spyralRange, const BuildingsMap& buildingsMap)
{
	for (int i = 0; i < spyralRange; i++)
	{
		TileCoord tile = entity.currentTile + coordSpyralArr[i];
		if (buildingsMap.buildingExists(tile) && buildingsMap.getTeamID(tile) != entity.team->getID())
			return pixel(tile);
	}
	return INCORRECT_PIXEL_COORD;
}


PixelCoord Aiming::aimOnEntity(const Entity& entity, const float pixelRange, const World& world)
{
	for (auto& [teamID, team] : world.getTeams())
	{
		if (entity.team->getID() != teamID)
		{
			auto& eList = team->getEneities().getList();
			for (auto& it : eList)
			{
				PixelCoord delta = entity.coord - it->getCoord();
				if (delta.x * delta.x + delta.y * delta.y < pixelRange * pixelRange)
					return it->getCoord();
			}
		}
	}
	return INCORRECT_PIXEL_COORD;
}


PixelCoord Aiming::aimOnEntity(const Turret& turret, const float pixelRange, const World& world)
{
	for (auto& [teamID, team] : world.getTeams())
	{
		if (turret.team->getID() != teamID)
		{
			auto& eList = team->getEneities().getList();
			for (auto& it : eList)
			{
				PixelCoord delta = turret.coord - it->getCoord();
				if (delta.x * delta.x + delta.y * delta.y < pixelRange * pixelRange)
					return it->getCoord();
			}
		}
	}
	return INCORRECT_PIXEL_COORD;
}


PixelCoord Aiming::aimOnShell(const Entity& entity, const float pixelRange, const World& world)
{
	for (auto& [teamID, team] : world.getTeams())
	{
		if (entity.team->getID() != teamID)
		{
			for (auto& shell : team->getShells().getList())
			{
				if (shell->getType() == ShellType::ROCKET)
				{
					PixelCoord delta = entity.coord - shell->getCoord();
					if (delta.x * delta.x + delta.y * delta.y < pixelRange * pixelRange)
						return shell->getCoord();
				}	
			}
		}
	}
	return INCORRECT_PIXEL_COORD;
}
