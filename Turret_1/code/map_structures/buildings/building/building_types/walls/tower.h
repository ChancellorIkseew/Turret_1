#pragma once
#ifndef TOWER_H
#define TOWER_H

#include "map_structures/buildings/building/building.h"
#include "map_structures/entities/turret.h"

class Tower : public Building
{
protected:

	Turret* turret;

public:

	Tower(char type, short durability, short size, int tileX, int tileY);
	Tower();
	virtual ~Tower();

	void save(std::ofstream& fout) const override;
	void load(std::ifstream& fin) override;

	void interact() override;

	bool isThisPositionFree(int position) const override;
	bool canAccept(int resType) const override;

	void setTurret(int turretType) override final;
	void removeTurret() override final;
	bool isTurretOnTower() const override final;

};


#endif // TOWER_H
