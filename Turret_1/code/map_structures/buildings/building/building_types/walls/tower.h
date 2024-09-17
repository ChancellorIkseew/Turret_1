#pragma once
#ifndef TOWER_H
#define TOWER_H

#include "../../building.h"
#include "../../../../entities/turrets.h"

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

	void setTurret(int turretType);
	void removeTurret();
	bool isTurretOnTower();

	virtual void draw(sf::RenderWindow& window) override = 0;

};


#endif // TOWER_H
