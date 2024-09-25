
#include "laser_bot.h"

#include "map_structures/shells/shells.h"
#include "map_structures/shells/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"


LaserBot::LaserBot(int type, PixelCoord coord, float curentAngleDeg, short curentDurability) :
	Entity(type, coord, curentAngleDeg, curentDurability)
{
	this->initCombatData();
}

LaserBot::LaserBot(int type) : Entity(type)
{
	this->initCombatData();
	durability = 10;
}

void LaserBot::initCombatData()
{
	Entity::initCombatData();
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
		shootingAngleDeg = atan2f(aimCoord.y - coord.y, aimCoord.x - coord.x) * 57.3f + 90;

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 4.5f;
			float correctionY = sin(shootingAngleRad) * 4.5f;	
			enemyShellsList.emplace_back(new Shell(AC_SHELL, coord.x - correctionX, coord.y + correctionY, shootingAngleRad, shootingAngleDeg));
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
