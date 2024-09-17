#pragma once
#ifndef ROCKET_BOSS_BOT_H
#define ROCKET_BOSS_BOT_H

#include <SFML\Graphics.hpp>

#include "../entities.h"
#include "../../base_engine/tile_coord.h"


class RocketBossBot : public Entity
{
private:

	void loadCombatData() override;

public:

	RocketBossBot(int v_entityType, float v_coordX, float v_coordY, float curentAngleDeg, short curentDurability);
	RocketBossBot(int v_entityType);
	~RocketBossBot();

	void findPath(BuildingsMap& buildingsMap1);
	void shooting(BuildingsMap& buildingsMap1, int time) override;
	TileCoord findShootingAim(BuildingsMap& buildingsMap1);

	void draw(sf::RenderWindow& window) override;

};

#endif // ROCKET_BOSS_BOT_H
