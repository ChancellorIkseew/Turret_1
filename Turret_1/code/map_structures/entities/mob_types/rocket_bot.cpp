
#include "rocket_bot.h"

#include "map_structures/shells/shell_types/rockets.h"
#include "map_structures/shells/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"


RocketBot::RocketBot(int type, PixelCoord coord, float curentAngleDeg, short curentDurability) :
	Entity(type, coord, curentAngleDeg, curentDurability)
{
	this->initCombatData();
}

RocketBot::RocketBot(int entityType) : Entity(entityType)
{
	this->initCombatData();
	durability = 25;
}

void RocketBot::initCombatData()
{
	Entity::initCombatData();
	range = 25;
	spyralRange = 2109;
	reload = 240;
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
		shootingAngleDeg = atan2f(aimCoord.y - coord.y, aimCoord.x - coord.x) * 57.3f + 90;

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 5;
			float correctionY = sin(shootingAngleRad) * 5;
			enemyShellsList.push_back(new Rocket(ROCKET, coord.x - correctionX, coord.y + correctionY, shootingAngleRad, shootingAngleDeg));
			reloadTimer = reload;
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
