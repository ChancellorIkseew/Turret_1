
#include "tower.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/entities/turret_types/autocannon_turret.h"
#include "map_structures/entities/turret_types/rocket_turret.h"


Tower::Tower(char type, short durability, short size, const TileCoord tile) : Building (type, durability, size, tile)
{
	turret = nullptr;
}


Tower::~Tower()
{
	delete turret;
	turret = nullptr;
}


void Tower::save(std::ofstream& fout) const
{
	if (turret != nullptr)
	{
		turret->save(fout);
	}
	else
	{
		fout << "!\n";
	}
	Building::save(fout);
}

void Tower::load(std::ifstream& fin)
{
	char nextSymbol;
	fin >> nextSymbol;
	if (nextSymbol != '!')
	{
		fin.seekg(-1, std::ios::cur);
		int turretType;
		fin >> turretType;
		turret = Turret::setTurret(turretType, tile.x, tile.y);
		turret->load(fin);
	}
	Building::load(fin);
}


void Tower::interact()
{
	if (turret != nullptr)
	{
		if (turret->needAmoo())
		{
			int resType = turret->getAmooType();
			if (isEnoughRes(resType, 1))
			{
				wasteResorce(resType, 1);
				turret->takeAmoo(resType);
			}
		}
		turret->shooting();
	}
}


bool Tower::isThisPositionFree(int position) const
{
	short comonResQuant = 0;

	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		comonResQuant = comonResQuant + it->quant;
	}

	if (comonResQuant < 21)
	{
		return true;
	}
	return false;
}


bool Tower::canAccept(int resType) const
{
	if (resType == RES_AC_SHELLS || resType == RES_ROCKET)
	{
		return true;
	}
	return false;
}


void Tower::setTurret(int turretType)
{
	switch (turretType)
	{
	case AUTOCANNON_TURRET:
		turret = new AutocannonTurret(AUTOCANNON_TURRET, tile.x, tile.y, 0, 0);
		break;

	case ROCKET_TURRET:
		turret = new RocketTurret(ROCKET_TURRET, tile.x, tile.y, 0, 0);
		break;

	}
}

void Tower::removeTurret()
{
	delete turret;
	turret = nullptr;
}

bool Tower::isTurretOnTower() const
{
	if (turret != nullptr)
	{
		return true;
	}
	return false;
}
