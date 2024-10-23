#pragma once
#ifndef AUTOCANNON_TURRET_H
#define AUTOCANNON_TURRET_H

#include <SFML\Graphics.hpp>
#include "map_structures/entities/turret/turret.h"


class AutocannonTurret : public Turret
{
	public:
		AutocannonTurret(const uint16_t type, const TileCoord tile, Team* const team);
		~AutocannonTurret() = default;

		void shooting() override final;
		
		void takeAmoo(const int resType) override final;
		int getAmooType() const override final;
		
		void draw(sf::RenderWindow& window) override final;

};

#endif // AUTOCANNON_TURRET_H
