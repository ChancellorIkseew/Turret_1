#pragma once
#ifndef CANNON_BOSS_BOT_H
#define CANNON_BOSS_BOT_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/entity.h"
#include "map_structures/base_engine/tile_coord.h"


class CannonBossBot : public Entity
{
private:

	void initCombatData() override final;

public:

	CannonBossBot(int type, float coordX, float coordY, float curentAngleDeg, short curentDurability);
	CannonBossBot(int type);
	~CannonBossBot() = default;

	void findPath(BuildingsMap& buildingsMap1) override final;
	void shooting(BuildingsMap& buildingsMap1, int time) override final;
	TileCoord findShootingAim(BuildingsMap& buildingsMap1) override final;

	void draw(sf::RenderWindow& window) override final;

};


#endif // CANNON_BOSS_BOT_H
