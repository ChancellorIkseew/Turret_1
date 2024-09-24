
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
		int tileX = this->newTileCoordX + coordSpyralArr[i].x;
		int tileY = this->newTileCoordY + coordSpyralArr[i].y;
		TileCoord tileCoord{ tileX, tileY };

		if (tileX > -1 && tileX < 100 && tileY > -1 && tileY < 100)
		{
			if (buildingsMap1.getBuildingType(tileCoord) == '0')
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
			int tileX = tile(coordX + sin(angleRad) * _TILE_ * i);
			int tileY = tile(coordY + cos(angleRad) * _TILE_ * i);
			TileCoord tileCoord{ tileX, tileY };

			if (buildingsMap1.getBuildingType(tileCoord) != VOID_)
			{
				return tileCoord;
			}
		}

		for (int i = 0; i < spyralRange; i++)
		{
			int tileX = this->newTileCoordX + coordSpyralArr[i].x;
			int tileY = this->newTileCoordY + coordSpyralArr[i].y;
			TileCoord tileCoord{ tileX, tileY };

			if (tileX > -1 && tileX < mapMaxX && tileY > -1 && tileY < mapMaxY)
			{
				if (buildingsMap1.getBuildingType(tileCoord) != VOID_)
				{
					return tileCoord;
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
