
#include "rocket_bot.h"

<<<<<<< Updated upstream
#include "map_structures/team/team.h"
=======
>>>>>>> Stashed changes
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"


RocketBot::RocketBot(int entityType, Team* team) : Entity(entityType, team)
{
	durability = 25 * enemyMobMaxDurabilityModifier;
	range = 25;
	spyralRange = 2109;
}


PixelCoord RocketBot::findDestinationCoord() const
{
	return Entity::findDestinationCoord();
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
<<<<<<< Updated upstream
			//team.spawnShell(ROCKET, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
=======
			team->spawnShell(ROCKET, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
>>>>>>> Stashed changes
			reloadTimer = 240;
		}
	}
}


PixelCoord RocketBot::findShootingAim() const
{
	return Entity::findShootingAim();
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
