
#include "laser_bot.h"

#include "map_structures/team/team.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"


LaserBot::LaserBot(Team* const team) : Entity(team)
{
	durability = 10 * world->getPreSettings().getMobs().maxDurabilityModifier;
	pixelRange = 8;
	spyralRange = 249;
}


void LaserBot::shoot(const BuildingsMap& buildingsMap)
{
	Entity::reloadWeapon();
	Entity::detectAim();

	PixelCoord newAim = Aiming::aimOnShell(*this, *world);
	if (newAim.valid())
	{
		aimCoord = newAim;
		isAimDetected = true;
	}

	if (isAimDetected)
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = t1::be::radToDegree(shootingAngleRad);

		if (reloadTimer <= 0)
		{
			team->spawnShell(ShellType::LASER, coord, shootingAngleRad, shootingAngleDeg);
			reloadTimer = 2;
		}
	}
}


void LaserBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(60, 0, 17, 15));
	entitySprite.setOrigin(9, 8);

	if (isAimDetected)
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(motionAngleDeg);

	entitySprite.setPosition(coord.x, coord.y);
	window.draw(entitySprite);
}
