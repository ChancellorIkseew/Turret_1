
#include "rocket_bot.h"

#include "map_structures/team/team.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"


RocketBot::RocketBot(const uint16_t type, Team* const team) : Entity(type, team)
{
	durability = 25 * maxDurabilityModifier;
	pixelRange = 25;
	spyralRange = 2109;
}


void RocketBot::shoot()
{
	Entity::detectAim();
	Entity::reloadWeapon();

	if (isAimDetected)
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = atan2f(aimCoord.y - coord.y, aimCoord.x - coord.x) * 57.3f + 90.0f;

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 5;
			float correctionY = sin(shootingAngleRad) * 5;

			team->spawnShell(ROCKET, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
			reloadTimer = 240;
		}
	}
}


void RocketBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(42, 0, 17, 18));
	entitySprite.setOrigin(8, 9);

	if (isAimDetected)
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(motionAngleDeg);

	entitySprite.setPosition(coord.x, coord.y);
	window.draw(entitySprite);
}
