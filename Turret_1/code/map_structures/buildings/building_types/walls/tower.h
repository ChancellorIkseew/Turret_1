#pragma once
#ifndef TOWER_H
#define TOWER_H

#include "map_structures/buildings/building/building.h"
#include "map_structures/entities/turret/turret.h"

class Tower : public Building
{
protected:
	std::unique_ptr<Turret> turret;

public:
	Tower(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	virtual ~Tower() = default;

	//void save(std::ofstream& fout) const override;
	//void load(std::ifstream& fin) override;

	void interact() override;
	bool canAccept(const uint16_t resType) const override;

	void setTurret(const BuildingType turretType) override final;
	void removeTurret() override final;
	bool isTurretOnTower() const override final;

};

#endif // TOWER_H
