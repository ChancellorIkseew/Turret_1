#pragma once
#ifndef ROCKET_TURRET_H
#define ROCKET_TURRET_H

#include <SFML\Graphics.hpp>
#include "map_structures/entities/turret/turret.h"


class RocketTurret : public Turret
{
	public:
		RocketTurret(const TileCoord tile, Team* const team);
		~RocketTurret() = default;

		void shooting() override final;
		
		void takeAmoo(const int resType) override final;
		int getAmooType() const override final;
		
		void draw(sf::RenderWindow& window) override final;

};

#endif // ROCKET_TURRET_H
