
#include "rocket_boss_bot.h"

#include "map_structures/shells/shell_types/rockets.h"
#include "map_structures/shells/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"


RocketBossBot::RocketBossBot(int type, PixelCoord coord, float curentAngleDeg, short curentDurability) :
	Entity(type, coord, curentAngleDeg, curentDurability)
{
	this->initCombatData();
}

RocketBossBot::RocketBossBot(int type) : Entity(type)
{
	this->initCombatData();
	durability = 230;
}

void RocketBossBot::initCombatData()
{
	Entity::initCombatData();
	range = 28;
	spyralRange = 2661;
	reload = 60;
}


PixelCoord RocketBossBot::findDestinationCoord() const
{
	return Entity::findDestinationCoord();
}


void RocketBossBot::shoot()
{
	Entity::detectAim();
	Entity::reloadWeapon();

	if (isAimDetected)
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = atan2f(aimCoord.y - coord.y, aimCoord.x - coord.x) * 57.3f + 90;

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 18;
			float correctionY = sin(shootingAngleRad) * 18;

			enemyShellsList.push_back(new Rocket(ROCKET, coord.x - correctionX, coord.y + correctionY, shootingAngleRad, shootingAngleDeg));
			enemyShellsList.push_back(new Rocket(ROCKET, coord.x + correctionX, coord.y - correctionY, shootingAngleRad, shootingAngleDeg));
			reloadTimer = reload;
		}
		else if (reloadTimer == (reload / 2))
		{
			float correctionX = cos(shootingAngleRad) * 14;
			float correctionY = sin(shootingAngleRad) * 14;

			enemyShellsList.push_back(new Rocket(ROCKET, coord.x - correctionX, coord.y + correctionY, shootingAngleRad, shootingAngleDeg));
			enemyShellsList.push_back(new Rocket(ROCKET, coord.x + correctionX, coord.y - correctionY, shootingAngleRad, shootingAngleDeg));
		}
	}
}


void RocketBossBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(0, 61, 41, 28));
	entitySprite.setOrigin(21.5, 14);

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
