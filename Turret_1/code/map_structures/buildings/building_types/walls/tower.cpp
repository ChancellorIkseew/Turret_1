
#include "tower.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/entities/turret/turret.h"


Tower::Tower(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building (durability, size, tile, team) { }


void Tower::save(cereal::BinaryOutputArchive& archive) const
{
	Building::save(archive);
	bool hasTurret = turret != nullptr;
	archive(hasTurret);
	if (hasTurret)
		archive(turret);
}

void Tower::load(cereal::BinaryInputArchive& archive)
{
	Building::load(archive);
	bool hasTurret;
	archive(hasTurret);
	if (hasTurret)
	{
		archive(turret);
		turret->setCoord(t1::be::pixel(tile));
	}	
}


void Tower::interact()
{
	if (turret == nullptr)
		return;
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


bool Tower::canAccept(const uint16_t resType) const
{
	if (resType == RES_AC_SHELLS || resType == RES_ROCKET)
	{
		if (!Building::isStorageFull(20))
			return true;
	}
	return false;
}


void Tower::setTurret(const BuildingType turretType)
{
	turret = std::move(Turret::createTurret(turretType, tile, this->getTeam()));
}

