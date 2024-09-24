#include "rocket_boss_bot.h"

#include "map_structures/shells/shell_types/rockets.h"
#include "map_structures/shells/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"


RocketBossBot::RocketBossBot(int type, float coordX, float coordY, float curentAngleDeg, short curentDurability) :
	Entity(type, coordX, coordY, curentAngleDeg, curentDurability)
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


void RocketBossBot::findPath(BuildingsMap& buildingsMap1)
{
	int minDistance = pow((newTileCoordX - 50), 2) + pow((newTileCoordY - 50), 2);
	int nIt = 0;

	for (int i = 1; i < 8; i = i + 2)
	{
		int tileX = this->newTileCoordX + coordSpyralArr[i].x;
		int tileY = this->newTileCoordY + coordSpyralArr[i].y;
		TileCoord tileCoord{ tileX, tileY };

		if (tileX > -1 && tileX < 100 && tileY > -1 && tileY < 100)
		{
			if (buildingsMap1.getBuildingType(tileCoord) == VOID_)
			{
				int distance = pow((tileX - 50), 2) + pow((tileY - 50), 2);
				if (distance < minDistance)
				{
					minDistance = distance;
					nIt = i;
				}
			}
		}

	}

	if (nIt != 0)
	{
		destCoordX = pixel(this->newTileCoordX + coordSpyralArr[nIt].x);
		destCoordY = pixel(this->newTileCoordY + coordSpyralArr[nIt].y);
	}
}



void RocketBossBot::shooting(BuildingsMap& buildingsMap1, int time)
{
	if (newTileCoordX != oldTileCoordX || newTileCoordY != oldTileCoordY || buildingsMap1.getIsMapChanged())
	{
		TileCoord aimTileCoord = this->findShootingAim(buildingsMap1);

		if (aimTileCoord.x != -1)	// "-1" - aim_was_not_detected
		{
			aimCoordX = pixel(aimTileCoord.x);
			aimCoordY = pixel(aimTileCoord.y);

			isAimDetected = true;
		}
		else
		{
			isAimDetected = false;
		}
	}

	if (isAimDetected)
	{
		shootingAngleRad = atan2f(aimCoordX - coordX, aimCoordY - coordY);
		shootingAngleDeg = atan2f(aimCoordY - coordY, aimCoordX - coordX) * 57.3f + 90;

		if (time % reload == 0)
		{
			float correctionX = cos(shootingAngleRad) * 18;
			float correctionY = sin(shootingAngleRad) * 18;

			enemyShellsList.push_back(new Rocket(ROCKET, coordX - correctionX, coordY + correctionY, shootingAngleRad, shootingAngleDeg));
			enemyShellsList.push_back(new Rocket(ROCKET, coordX + correctionX, coordY - correctionY, shootingAngleRad, shootingAngleDeg));
		}
		else if (time % reload == 30)
		{
			float correctionX = cos(shootingAngleRad) * 14;
			float correctionY = sin(shootingAngleRad) * 14;

			enemyShellsList.push_back(new Rocket(ROCKET, coordX - correctionX, coordY + correctionY, shootingAngleRad, shootingAngleDeg));
			enemyShellsList.push_back(new Rocket(ROCKET, coordX + correctionX, coordY - correctionY, shootingAngleRad, shootingAngleDeg));
		}
	}
}



TileCoord RocketBossBot::findShootingAim(BuildingsMap& buildingsMap1)
{
	if (true)
	{
		for (int i = 1; i <= range; i++)
		{

			int tileX = tile(coordX + sin(angleRad) * 16 * i);
			int tileY = tile(coordY + cos(angleRad) * 16 * i);
			TileCoord tileCoord{ tileX, tileY };

			if (buildingsMap1.getBuildingType(tileCoord) != VOID_)
			{
				return { tileCoord };
			}
		}

		for (int i = 0; i < spyralRange; i++)
		{
			int tileX = this->newTileCoordX + coordSpyralArr[i].x;
			int tileY = this->newTileCoordY + coordSpyralArr[i].y;
			TileCoord tileCoord{ tileX, tileY };

			if (tileX > -1 && tileX < 101 && tileY > -1 && tileY < 101)
			{
				if (buildingsMap1.getBuildingType(tileCoord) != VOID_)
				{
					return { tileCoord };
				}
			}
		}

	}

	return { -1, -1 };
}



void RocketBossBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(0, 61, 41, 28));
	entitySprite.setOrigin(21.5, 14);

	if (isAimDetected)
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(angleDeg);

	entitySprite.setPosition(coordX, coordY);
	window.draw(entitySprite);

	if (durability > 110)    //Boss_energy_shield
	{
		shieldSprite.setPosition(coordX, coordY);
		window.draw(shieldSprite);
	}
}
