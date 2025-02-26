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
	Tower(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	Tower() = default;
	virtual ~Tower() = default;

	void save(cereal::BinaryOutputArchive& archive) const override final;
	void load(cereal::BinaryInputArchive& archive) override final;

	void interact() override final;
	bool canAccept(const ResType resType) const override final;

	void setTurret(const BuildingType turretType);
	void removeTurret() { turret.reset(); }
	bool isTurretOnTower() const { return turret != nullptr; }

};

#endif // TOWER_H
