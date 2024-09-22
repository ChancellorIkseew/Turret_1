
#include "rocket_bot.h"

#include "map_structures/shells/shell_types/rockets.h"
#include "map_structures/shells/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"


RocketBot::RocketBot(int type, float coordX, float coordY, float curentAngleDeg, short curentDurability) :
	Entity(type, coordX, coordY, curentAngleDeg, curentDurability)
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


void RocketBot::findPath(BuildingsMap& buildingsMap1)
{
	int minDistance = pow((newTileCoordX - 50), 2) + pow((newTileCoordY - 50), 2);
	int nIt = 0;

	for (int i = 1; i < 8; i = i + 2)
	{
		int tileCoordX = this->newTileCoordX + coordSpyralArr[i].x;
		int tileCoordY = this->newTileCoordY + coordSpyralArr[i].y;

		if (tileCoordX > -1 && tileCoordX < 100 && tileCoordY > -1 && tileCoordY < 100)
		{
			if (buildingsMap1.getBuildingType(tileCoordX, tileCoordY) == '0')
			{
				int distance = pow((tileCoordX - 50), 2) + pow((tileCoordY - 50), 2);
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



void RocketBot::shooting(BuildingsMap& buildingsMap1, int time)
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
			float correctionX = cos(shootingAngleRad) * 5;
			float correctionY = sin(shootingAngleRad) * 5;

			enemyShellsList.push_back(new Rocket(ROCKET, coordX - correctionX, coordY + correctionY, shootingAngleRad, shootingAngleDeg));
		}
	}
}



TileCoord RocketBot::findShootingAim(BuildingsMap& buildingsMap1)
{
	if (true)
	{
		for (int i = 1; i <= range; i++)
		{
			int tileCoordX = tile(coordX + sin(angleRad) * _TILE_ * i);
			int tileCoordY = tile(coordY + cos(angleRad) * _TILE_ * i);

			if (buildingsMap1.getBuildingType(tileCoordX, tileCoordY) != VOID_)
			{
				return { tileCoordX, tileCoordY };
			}
		}

		for (int i = 0; i < spyralRange; i++)
		{
			int tileCoordX = this->newTileCoordX + coordSpyralArr[i].x;
			int tileCoordY = this->newTileCoordY + coordSpyralArr[i].y;

			if (tileCoordX > -1 && tileCoordX < mapMaxX && tileCoordY > -1 && tileCoordY < mapMaxY)
			{
				if (buildingsMap1.getBuildingType(tileCoordX, tileCoordY) != VOID_)
				{
					return { tileCoordX, tileCoordY };
				}
			}
		}
	}

	return { -1, -1 };
}



void RocketBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(42, 0, 17, 18));
	entitySprite.setOrigin(8, 9);

	if (isAimDetected)
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(angleDeg);

	entitySprite.setPosition(coordX, coordY);
	window.draw(entitySprite);
}
