#pragma once
#ifndef STANDARD_BOT_H
#define STANDARD_BOT_H

#include <SFML\Graphics.hpp>

#include "../entities.h"
#include "../../base_engine/tile_coord.h"


class StandardBot : public Entity
{
private:

	void loadCombatData() override;

public:

	StandardBot(int v_entityType, float v_coordX, float v_coordY, float curentAngleDeg, short curentDurability);
	StandardBot(int v_entityType);
	~StandardBot();

	void findPath(BuildingsMap& buildingsMap1) override;
	void shooting(BuildingsMap& buildingsMap1, int time) override;
	TileCoord findShootingAim(BuildingsMap& buildingsMap1);

	void draw(sf::RenderWindow& window) override;

};

#endif // STANDARD_BOT_H
