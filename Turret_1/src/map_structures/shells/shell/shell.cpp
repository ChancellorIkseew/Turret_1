
#include "shell.h"

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"


Shell::Shell(const PixelCoord coord, float angleRad, Team* const team) :
	coord(coord), angleRad(angleRad), team(team) { }

void Shell::save(cereal::BinaryOutputArchive& archive) const
{
	archive(coord, lineMotion, angleRad, restLifeTime);
}

void Shell::load(cereal::BinaryInputArchive& archive)
{
	archive(coord, lineMotion, angleRad, restLifeTime);
}


void Shell::motion()
{
	coord.x += lineMotion.x;
	coord.y += lineMotion.y;
	if(--restLifeTime < 1)
		isWasted = true;
}

void Shell::tryHitting()
{
	TileCoord tile = t1::be::tile(coord);
	BuildingsMap& buildingsMap = world->getBuildingsMap();
	if (!buildingsMap.isVoidBuilding(tile) && buildingsMap.getTeamID(tile) != team->getID())
	{
		const float modifiedDamage = getDirectDamage() * world->getPreSettings().getShells().directDamageModifier;
		buildingsMap.setDamage(modifiedDamage, tile);
		isWasted = true;
		return;
	}

	for (auto& team : world->getTeams())
	{
		if (this->team->getID() != team.first)
		{
			for (auto& entity : team.second->getEneities().getList())
			{
				if (abs(entity->getCoord().x - coord.x) < 7 && abs(entity->getCoord().y - coord.y) < 7)
				{
					const float modifiedDamage = getDirectDamage() * world->getPreSettings().getShells().directDamageModifier;
					entity->setDamage(modifiedDamage);
					isWasted = true;
					return;
				}
			}
		}
	}
}


void Shell::prepareSprites()
{
	shellImage.loadFromFile("images/bullet.bmp");
	shellImage.createMaskFromColor(sf::Color(0, 255, 0));
	shellTexture.loadFromImage(shellImage);
}
