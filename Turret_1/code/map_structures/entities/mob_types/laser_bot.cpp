
#include "laser_bot.h"

#include "map_structures/team/team.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"


LaserBot::LaserBot(const uint16_t type, Team* const team) : Entity(type, team)
{
	durability = 10 * maxDurabilityModifier;
	pixelRange = 8;
	spyralRange = 249;
}


void LaserBot::shoot()
{
	Entity::detectAim();
	Entity::reloadWeapon();

	if (isAimDetected)
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = atan2f(aimCoord.y - coord.y, aimCoord.x - coord.x) * 57.3f + 90.0f;

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 4.5f;
			float correctionY = sin(shootingAngleRad) * 4.5f;

			team->spawnShell(AC_SHELL, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
			reloadTimer = 60;
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
