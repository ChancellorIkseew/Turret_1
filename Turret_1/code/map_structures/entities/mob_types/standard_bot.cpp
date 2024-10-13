
#include "standard_bot.h"

<<<<<<< Updated upstream
#include "map_structures/team/team.h"
=======
>>>>>>> Stashed changes
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"


StandardBot::StandardBot(int type, Team* team) : Entity(type, team)
{
	durability = 10 * enemyMobMaxDurabilityModifier;
	range = 5;
	spyralRange = 109;
}


void StandardBot::shoot()
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
<<<<<<< Updated upstream
			//team.spawnShell(AC_SHELL, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
=======
			team->spawnShell(AC_SHELL, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
>>>>>>> Stashed changes
			reloadTimer = 30;
		}
	}
}


void StandardBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(1, 1, 15, 13));
	entitySprite.setOrigin(8, 7);

	if (isAimDetected)
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(motionAngleDeg);

	entitySprite.setPosition(coord.x, coord.y);
	window.draw(entitySprite);
}
