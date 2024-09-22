#pragma once
#ifndef STANDARD_BOT_H
#define STANDARD_BOT_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/entity.h"
#include "map_structures/base_engine/tile_coord.h"


class StandardBot : public Entity
{
private:

	void initCombatData() override final;

public:

	StandardBot(int type, float coordX, float coordY, float curentAngleDeg, short curentDurability);
	StandardBot(int type);
	~StandardBot() = default;

	void findPath(BuildingsMap& buildingsMap1) override  final;
	void shooting(BuildingsMap& buildingsMap1, int time) override final;
	TileCoord findShootingAim(BuildingsMap& buildingsMap1) override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // STANDARD_BOT_H
