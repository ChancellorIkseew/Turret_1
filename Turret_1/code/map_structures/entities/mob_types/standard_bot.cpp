
#include "standard_bot.h"

#include "map_structures/team/team.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"


StandardBot::StandardBot(Team* const team) : Entity(team)
{
	durability = 10 * maxDurabilityModifier;
	pixelRange = 5;
	spyralRange = 109;
}


void StandardBot::shoot(const BuildingsMap& buildingsMap)
{
	Entity::reloadWeapon();
	
	if (isAimDetected)
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = t1::be::radToDegree(shootingAngleRad);

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 4.5f;
			float correctionY = sin(shootingAngleRad) * 4.5f;	

			team->spawnShell(AC_SHELL, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
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
