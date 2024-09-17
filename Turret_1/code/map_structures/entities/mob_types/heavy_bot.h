#pragma once
#ifndef HEAVY_BOT_H
#define HEAVY_BOT_H

#include <SFML\Graphics.hpp>

#include "../entities.h"
#include "../../base_engine/tile_coord.h"


class HeavyBot : public Entity
{
private:

	void loadCombatData() override;

public:

	HeavyBot(int v_entityType, float v_coordX, float v_coordY, float curentAngleDeg, short curentDurability);
	HeavyBot(int v_entityType);
	~HeavyBot();

	void findPath(BuildingsMap& buildingsMap1) override;
	void shooting(BuildingsMap& buildingsMap1, int time) override;
	TileCoord findShootingAim(BuildingsMap& buildingsMap1);

	void draw(sf::RenderWindow& window) override;

};

#endif // HEAVY_BOT_H
