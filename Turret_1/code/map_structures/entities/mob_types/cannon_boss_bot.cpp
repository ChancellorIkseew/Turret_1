#include "cannon_boss_bot.h"

#include "map_structures/shells/shell_types/heavy_shell.h"
#include "map_structures/shells/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"


CannonBossBot::CannonBossBot(int type, PixelCoord coord, float curentAngleDeg, short curentDurability) :
	Entity(type, coord, curentAngleDeg, curentDurability)
{
	this->initCombatData();
}

CannonBossBot::CannonBossBot(int type) : Entity(type)
{
	this->initCombatData();
	durability = 270;
}


void CannonBossBot::initCombatData()
{
	Entity::initCombatData();
	range = 20;
	spyralRange = 1369;
	reload = 30;
}


PixelCoord CannonBossBot::findDestinationCoord() const
{
	return Entity::findDestinationCoord();
}



void CannonBossBot::shoot()
{
	Entity::detectAim();
	Entity::reloadWeapon();

	if (isAimDetected)
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = atan2f(aimCoord.y - coord.y, aimCoord.x - coord.x) * 57.3f + 90;

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 15;
			float correctionY = sin(shootingAngleRad) * 15;

			enemyShellsList.push_back(new HeavyShell(HEAVY_SHELL, coord.x - correctionX, coord.y + correctionY, shootingAngleRad, shootingAngleDeg));
			enemyShellsList.push_back(new HeavyShell(HEAVY_SHELL, coord.x + correctionX, coord.y - correctionY, shootingAngleRad, shootingAngleDeg));
			reloadTimer = reload;
		}
	}
}


void CannonBossBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(0, 19, 41, 41));
	entitySprite.setOrigin(21, 21);

	if (isAimDetected)
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(motionAngleDeg);

	entitySprite.setPosition(coord.x, coord.y);
	window.draw(entitySprite);

	if (durability > 150)    //Boss_energy_shield
	{
		shieldSprite.setPosition(coord.x, coord.y);
		window.draw(shieldSprite);
	}
}
