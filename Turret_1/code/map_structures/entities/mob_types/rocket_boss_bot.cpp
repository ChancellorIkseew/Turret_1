
#include "rocket_boss_bot.h"

#include "map_structures/team/team.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"


RocketBossBot::RocketBossBot(Team* const team) : Entity(team)
{
	durability = 230 * maxDurabilityModifier;
	pixelRange = 28;
	spyralRange = 2661;
}


void RocketBossBot::shoot(const BuildingsMap& buildingsMap)
{
	Entity::reloadWeapon();

	if (isAimDetected)
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = t1::be::radToDegree(shootingAngleRad);

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 18;
			float correctionY = sin(shootingAngleRad) * 18;

			team->spawnShell(ROCKET, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
			team->spawnShell(ROCKET, { coord.x + correctionX, coord.y - correctionY }, shootingAngleRad, shootingAngleDeg);
			reloadTimer = 60;
		}
		else if (reloadTimer == 30)
		{
			float correctionX = cos(shootingAngleRad) * 14;
			float correctionY = sin(shootingAngleRad) * 14;

			team->spawnShell(ROCKET, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
			team->spawnShell(ROCKET, { coord.x + correctionX, coord.y - correctionY }, shootingAngleRad, shootingAngleDeg);
		}
	}
}


void RocketBossBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(0, 62, 47, 30));
	entitySprite.setOrigin(24, 14);

	if (isAimDetected)
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(motionAngleDeg);

	entitySprite.setPosition(coord.x, coord.y);
	window.draw(entitySprite);

	if (durability > 110)    //Boss_energy_shield
	{
		shieldSprite.setPosition(coord.x, coord.y);
		window.draw(shieldSprite);
	}
}
