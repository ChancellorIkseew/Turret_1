
#include "heavy_bot.h"

#include "map_structures/shells/shell/shell.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/shells/shells_list/shells_list.h"
#include "map_structures/buildings/building/buildings_enum.h"


HeavyBot::HeavyBot(int type) : Entity(type)
{
	durability = 50 * enemyMobMaxDurabilityModifier;
	range = 7;
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

			t1::sh::enemyShellsList.emplace_back(Shell::createShell(AC_SHELL, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg));
			t1::sh::enemyShellsList.emplace_back(Shell::createShell(AC_SHELL, { coord.x + correctionX, coord.y - correctionY }, shootingAngleRad, shootingAngleDeg));
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
