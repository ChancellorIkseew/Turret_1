
#include "tower.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/entities/turret_types/autocannon_turret.h"
#include "map_structures/entities/turret_types/rocket_turret.h"


Tower::Tower(char type, short durability, short size, const TileCoord tile, Team* team) : Building (type, durability, size, tile, team)
{
	turret = nullptr;
}


void Tower::save(std::ofstream& fout) const
{
	if (turret != nullptr)
		turret->save(fout);
	else
		fout << "!\n";
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
		turret = std::move(Turret::createTurret(turretType, tile, this->getTeam()));
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


bool Tower::canAccept(const uint16_t resType) const
{
	if (resType == RES_AC_SHELLS || resType == RES_ROCKET)
	{
		if (!Building::isStorageFull(20))
		return true;
	}
	return false;
}


void Tower::setTurret(int turretType)
{
	turret = std::move(Turret::createTurret(turretType, tile, this->getTeam()));
}

void Tower::removeTurret()
{
	turret.reset();
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
