#include "cannon_boss_bot.h"

#include "../../shells/shells.h"
#include "../../shells/shell_types/rockets.h"
#include "../../buildings/building/buildings_enum.h"


CannonBossBot::CannonBossBot(int v_entityType, float v_coordX, float v_coordY, float curentAngleDeg, short curentDurability) :
	Entity(v_entityType, v_coordX, v_coordY, curentAngleDeg, curentDurability)
{
	loadCombatData();
	++enemyMobsQuantity;
}

CannonBossBot::CannonBossBot(int v_entityType) : Entity(v_entityType)
{
	durability = 2700;
	loadCombatData();
	++enemyMobsQuantity;
}

CannonBossBot::~CannonBossBot()
{
	--enemyMobsQuantity;
}

void CannonBossBot::loadCombatData()
{
	range = 20;
	spyralRange = 1369;
	reload = 30;

	isAimDetected = false;

	aimCoordX = mapMaxX * _HALF_TILE_;
	aimCoordY = mapMaxY * _HALF_TILE_;

	destCoordX = aimCoordX;
	destCoordY = aimCoordY;
}


void CannonBossBot::findPath(BuildingsMap& buildingsMap1)
{
	int minDistance = pow((newTileCoordX - 50), 2) + pow((newTileCoordY - 50), 2);
	int nIt = 0;

	for (int i = 1; i < 8; i = i + 2)
	{
		int tileCoordX = this->newTileCoordX + coordSpyralArr[i].x;
		int tileCoordY = this->newTileCoordY + coordSpyralArr[i].y;

		if (tileCoordX > -1 && tileCoordX < 100 && tileCoordY > -1 && tileCoordY < 100)
		{
			if (buildingsMap1.getBuildingType(tileCoordX, tileCoordY) == VOID_)
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

	std::cout << "x:" << destCoordX << " y:" << destCoordY << '\n';
}



void CannonBossBot::shooting(BuildingsMap& buildingsMap1, int time)
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
			float correctionX = cos(shootingAngleRad) * 15;
			float correctionY = sin(shootingAngleRad) * 15;

			enemyShellsList.push_back(new Shell('2', coordX - correctionX, coordY + correctionY, shootingAngleRad, shootingAngleDeg));
			enemyShellsList.push_back(new Shell('2', coordX + correctionX, coordY - correctionY, shootingAngleRad, shootingAngleDeg));
		}
	}
}



TileCoord CannonBossBot::findShootingAim(BuildingsMap& buildingsMap1)
{
	if (true)
	{
		for (int i = 1; i <= range; i++)
		{

			int tileCoordX = tile(coordX + sin(angleRad) * 16 * i);
			int tileCoordY = tile(coordY + cos(angleRad) * 16 * i);

			if (buildingsMap1.getBuildingType(tileCoordX, tileCoordY) != VOID_)
			{
				std::cout << "b_type: " << buildingsMap1.getBuildingType(tileCoordX, tileCoordY) << " x: " << tileCoordX << " y: " << tileCoordY << '\n';
				return { tileCoordX, tileCoordY };
			}
		}

		for (int i = 0; i < spyralRange; i++)
		{
			int tileCoordX = this->newTileCoordX + coordSpyralArr[i].x;
			int tileCoordY = this->newTileCoordY + coordSpyralArr[i].y;

			if (tileCoordX > -1 && tileCoordX < 101 && tileCoordY > -1 && tileCoordY < 101)
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



void CannonBossBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(0, 19, 41, 41));
	entitySprite.setOrigin(21, 21);

	if (isAimDetected)
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(angleDeg);

	entitySprite.setPosition(coordX, coordY);
	window.draw(entitySprite);

	if (durability > 1500)    //Boss_energy_shield
	{
		shieldSprite.setPosition(coordX, coordY);
		window.draw(shieldSprite);
	}
}