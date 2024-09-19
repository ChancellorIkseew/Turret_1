
#include "tower.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/entities/turret_types/autocannon_turret.h"
#include "map_structures/entities/turret_types/rocket_turret.h"


Tower::Tower(char v_type, short v_durability, short v_size, int tileX, int tileY) : Building (v_type, v_durability, v_size, tileX, tileY)
{
	turret = nullptr;
}

Tower::Tower() : Building()
{
	turret = nullptr;
}

Tower::~Tower()
{
	delete turret;
	turret = nullptr;
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


bool Tower::isThisPositionFree(int position)
{
	short comonResQuant = 0;

	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		comonResQuant = comonResQuant + it->quant;
			
	}

	if (comonResQuant < 21)
	{
		return true;
	}
	return false;
}


bool Tower::canAccept(int resType)
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
		turret = new AutocannonTurret(AUTOCANNON_TURRET, tileX, tileY, 0, 0);
		break;

	case ROCKET_TURRET:
		turret = new RocketTurret(ROCKET_TURRET, tileX, tileY, 0, 0);
		break;

	}
}

void Tower::removeTurret()
{
	delete turret;
	turret = nullptr;
}

bool Tower::isTurretOnTower()
{
	if (turret != nullptr)
	{
		return true;
	}
	return false;
}



void Tower::save(std::ofstream& fout)
{
	fout << type << " " << size << " " << durability <<
		" " << tileX << " " << tileY << '\n';

	if (turret != nullptr)
	{
		turret->save(fout);
	}
	else
	{
		fout << "!\n";
	}

	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		if (it->quant != 0)
			fout << it->type << " " << it->quant << '\n';
	}

	fout << "$\n";
}



void Tower::load(std::ifstream& fin)
{
	fin >> size >> durability >> tileX >> tileY;

	char nextSymbol;
	fin >> nextSymbol;

	if (nextSymbol != '!')
	{
		fin.seekg(-1, std::ios::cur);
		int turretType;
		fin >> turretType;
		turret = Turret::setTurret(turretType, tileX, tileY);
		turret->load(fin);
	}

	while (true)
	{
		fin >> nextSymbol;

		if (nextSymbol != '$')
		{
			fin.seekg(-1, std::ios::cur);
			int resType;
			fin >> resType;
			short amount;
			fin >> amount;
			storedResourcesList.emplace_back(StoredResource{ resType, amount });
		}
		else
		{
			break;
		}
	}
}
