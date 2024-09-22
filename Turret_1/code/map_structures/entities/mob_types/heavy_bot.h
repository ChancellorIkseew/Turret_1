#pragma once
#ifndef HEAVY_BOT_H
#define HEAVY_BOT_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/entity.h"
#include "map_structures/base_engine/tile_coord.h"


class HeavyBot : public Entity
{
private:

	void initCombatData() override final;

public:

	HeavyBot(int type, float coordX, float coordY, float curentAngleDeg, short curentDurability);
	HeavyBot(int type);
	~HeavyBot() = default;

	void findPath(BuildingsMap& buildingsMap1) override final;
	void shooting(BuildingsMap& buildingsMap1, int time) override final;
	TileCoord findShootingAim(BuildingsMap& buildingsMap1) override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // HEAVY_BOT_H
