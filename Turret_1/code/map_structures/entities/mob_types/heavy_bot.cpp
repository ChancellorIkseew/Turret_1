
#include "heavy_bot.h"

#include "map_structures/team/team.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"


HeavyBot::HeavyBot(const uint16_t type, Team* const team) : Entity(type, team)
{
	durability = 50 * maxDurabilityModifier;
	pixelRange = 7;
	spyralRange = 193;
}


void HeavyBot::shoot()
{
	Entity::detectAim();
	Entity::reloadWeapon();

	if (isAimDetected)
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = atan2f(aimCoord.y - coord.y, aimCoord.x - coord.x) * 57.3f + 90.0f;

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 8;
			float correctionY = sin(shootingAngleRad) * 8;

			team->spawnShell(AC_SHELL, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
			team->spawnShell(AC_SHELL, { coord.x + correctionX, coord.y - correctionY }, shootingAngleRad, shootingAngleDeg);
			reloadTimer = 15;
		}
	}
}


void HeavyBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(17, 0, 24, 18));
	entitySprite.setOrigin(12, 9);

	if (isAimDetected)
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(motionAngleDeg);

	entitySprite.setPosition(coord.x, coord.y);
	window.draw(entitySprite);
}
