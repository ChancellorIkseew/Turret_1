
#include "rocket_bot.h"

#include "map_structures/shells/shell/shell.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/shells/shells_list/shells_list.h"
#include "map_structures/buildings/building/buildings_enum.h"


RocketBot::RocketBot(int entityType) : Entity(entityType)
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
			t1::sh::enemyShellsList.push_back(Shell::createShell(ROCKET, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg));
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
