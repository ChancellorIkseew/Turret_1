
#include "heavy_bot.h"

#include "map_structures/shells/shells.h"
#include "map_structures/shells/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"


HeavyBot::HeavyBot(int type, PixelCoord coordY, float curentAngleDeg, short curentDurability) :
	Entity(type, coord, curentAngleDeg, curentDurability)
{
	this->initCombatData();
}

HeavyBot::HeavyBot(int type) : Entity(type)
{
	this->initCombatData();
	durability = 50;
}

void HeavyBot::initCombatData()
{
	Entity::initCombatData();
	range = 7;
	spyralRange = 193;
	reload = 15;
}


void HeavyBot::shoot()
{
	Entity::detectAim();
	Entity::reloadWeapon();

	if (isAimDetected)
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = atan2f(aimCoord.y - coord.y, aimCoord.x - coord.x) * 57.3f + 90;

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 8;
			float correctionY = sin(shootingAngleRad) * 8;

			enemyShellsList.emplace_back(new Shell(AC_SHELL, coord.x - correctionX, coord.y + correctionY, shootingAngleRad, shootingAngleDeg));
			enemyShellsList.emplace_back(new Shell(AC_SHELL, coord.x + correctionX, coord.y - correctionY, shootingAngleRad, shootingAngleDeg));
			reloadTimer = reload;
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
