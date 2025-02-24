
#include "tower.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/entities/turret_types/autocannon_turret.h"
#include "map_structures/entities/turret_types/rocket_turret.h"


Tower::Tower(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building (durability, size, tile, team) { }


void Tower::save(cereal::BinaryOutputArchive& archive) const
{
	archive(cereal::virtual_base_class<Building>(this));
	if (turret != nullptr)
		archive(true, turret);
	archive(false);
}

void Tower::load(cereal::BinaryInputArchive& archive)
{
	archive(cereal::virtual_base_class<Building>(this));
	bool hasTurret;
	archive(hasTurret);
	if (hasTurret)
		archive(turret);
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

