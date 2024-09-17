#pragma once
#ifndef CANNON_BOSS_BOT_H
#define CANNON_BOSS_BOT_H

#include <SFML\Graphics.hpp>

#include "../entities.h"
#include "../../base_engine/tile_coord.h"


class CannonBossBot : public Entity
{
private:

	void loadCombatData() override;

public:

	CannonBossBot(int v_entityType, float v_coordX, float v_coordY, float curentAngleDeg, short curentDurability);
	CannonBossBot(int v_entityType);
	~CannonBossBot();

	void findPath(BuildingsMap& buildingsMap1);
	void shooting(BuildingsMap& buildingsMap1, int time) override;
	TileCoord findShootingAim(BuildingsMap& buildingsMap1);

	void draw(sf::RenderWindow& window) override;

};

#endif // CANNON_BOSS_BOT_H
