
#include "heavy_bot.h"

#include "map_structures/team/team.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"


HeavyBot::HeavyBot(Team* const team) : Entity(team)
{
	durability = 50 * world->getPreSettings().getMobs().maxDurabilityModifier;
	pixelRange = 7;
	spyralRange = 193;
}


void HeavyBot::shoot(const BuildingsMap& buildingsMap)
{
	Entity::reloadWeapon();
	Entity::detectAim();

	if (isAimDetected)
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = t1::be::radToDegree(shootingAngleRad);

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 8.0f;
			float correctionY = sin(shootingAngleRad) * 8.0f;

			team->spawnShell(ShellType::AC_SHELL, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
			team->spawnShell(ShellType::AC_SHELL, { coord.x + correctionX, coord.y - correctionY }, shootingAngleRad, shootingAngleDeg);
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
