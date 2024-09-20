#pragma once
#ifndef TOWER_H
#define TOWER_H

#include "map_structures/buildings/building/building.h"
#include "map_structures/entities/turrets.h"

class Tower : public Building
{
protected:

	Turret* turret;

public:

	Tower(char v_type, short v_durability, short v_size, int tileX, int tileY);
	Tower();
	virtual ~Tower();

	void save(std::ofstream& fout) override;
	void load(std::ifstream& fin) override;

	void interact() override;

	bool isThisPositionFree(int position) override;
	bool canAccept(int resType) override;

	void setTurret(int turretType) override final;
	void removeTurret() override final;
	bool isTurretOnTower() override final;

};


#endif // TOWER_H
