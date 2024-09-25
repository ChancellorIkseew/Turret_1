
#include "standard_bot.h"

#include "map_structures/shells/shells.h"
#include "map_structures/shells/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"


StandardBot::StandardBot(int type, PixelCoord coord, float curentAngleDeg, short curentDurability) :
	Entity(type, coord, curentAngleDeg, curentDurability)
{
	this->initCombatData();
}

StandardBot::StandardBot(int type) : Entity(type)
{
	this->initCombatData();
	durability = 10;
}

void StandardBot::initCombatData()
{
	Entity::initCombatData();
	range = 5;
	spyralRange = 109;
	reload = 30;
}


void StandardBot::shoot()
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
