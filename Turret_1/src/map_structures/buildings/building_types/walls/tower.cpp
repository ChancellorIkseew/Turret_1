
#include "tower.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/entities/turret/turret.h"

constexpr short STORAGE_CAPACITY = 20;

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
		ResType resType = turret->getAmooType();
		if (isEnoughRes(resType, 1))
		{
			wasteResorce(resType, 1);
			turret->takeAmoo(resType);
		}
	}
	turret->shooting();
}


bool Tower::canAccept(const ResType resType) const
{
	if (resType != ResType::AC_SHELLS && resType != ResType::ROCKET)
		return false;
	return !Building::isStorageFull(STORAGE_CAPACITY);
}


void Tower::setTurret(const BuildingType turretType)
{
	turret = std::move(Turret::createTurret(turretType, tile, this->getTeam()));
}

