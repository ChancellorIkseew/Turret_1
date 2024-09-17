#pragma once
#ifndef LASER_BOT_H
#define LASER_BOT_H

#include <SFML\Graphics.hpp>

#include "../entities.h"
#include "../../base_engine/tile_coord.h"


class LaserBot : public Entity
{
private:

	void loadCombatData() override;

public:

	LaserBot(int v_entityType, float v_coordX, float v_coordY, float curentAngleDeg, short curentDurability);
	LaserBot(int v_entityType);
	~LaserBot();

	void findPath(BuildingsMap& buildingsMap1) override;
	void shooting(BuildingsMap& buildingsMap1, int time) override;
	TileCoord findShootingAim(BuildingsMap& buildingsMap1);

	void draw(sf::RenderWindow& window) override;

};

#endif // LASER_BOT_H
