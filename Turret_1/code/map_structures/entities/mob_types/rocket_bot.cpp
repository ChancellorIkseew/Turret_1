
#include "rocket_bot.h"

#include "map_structures/team/team.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"


RocketBot::RocketBot(Team* const team) : Entity(team)
{
	durability = 25 * world->getPreSettings().getMobs().maxDurabilityModifier;
	pixelRange = 25;
	spyralRange = 2109;
}


void RocketBot::shoot(const BuildingsMap& buildingsMap)
{
	Entity::reloadWeapon();

	if (isAimDetected)
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = t1::be::radToDegree(shootingAngleRad);

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 5.0f;
			float correctionY = sin(shootingAngleRad) * 5.0f;

			team->spawnShell(ShellType::ROCKET, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
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
