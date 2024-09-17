#pragma once
#ifndef SNIPER_BOT_H
#define SNIPER_BOT_H

#include <iostream>

#include <SFML\Graphics.hpp>

#include "../entities.h"
#include "../../base_engine/tile_coord.h"


class RocketBot : public Entity
{
private:

	void loadCombatData() override;

public:

	RocketBot(int v_entityType);
	RocketBot(int v_entityType, float v_coordX, float v_coordY, float curentAngleDeg, short curentDurability);
	~RocketBot();

	void findPath(BuildingsMap& buildingsMap1) override;
	void shooting(BuildingsMap& buildingsMap1, int time) override;
	TileCoord findShootingAim(BuildingsMap& buildingsMap1);

	void draw(sf::RenderWindow& window) override;

};

#endif // SNIPER_BOT_H
