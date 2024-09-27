
#include "laser_bot.h"

#include "map_structures/shells/shell/shell.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/shells/shells_list/shells_list.h"
#include "map_structures/buildings/building/buildings_enum.h"


LaserBot::LaserBot(int type) : Entity(type)
{
	durability = 10 * enemyMobMaxDurabilityModifier;
	range = 8;
	spyralRange = 249;
	reload = 60;
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
			t1::sh::enemyShellsList.emplace_back(Shell::createShell(AC_SHELL, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg));
			reloadTimer = reload;
		}
	}
}


PixelCoord LaserBot::findShootingAim() const
{
	return Entity::findShootingAim();
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
