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
	Tower(char type, short durability, short size, const TileCoord tile, Team* team);
	virtual ~Tower() = default;

	void save(std::ofstream& fout) const override;
	void load(std::ifstream& fin) override;

	void interact() override;
	bool canAccept(const uint16_t resType) const override;

	void setTurret(int turretType) override final;
	void removeTurret() override final;
	bool isTurretOnTower() const override final;

};

#endif // TOWER_H
