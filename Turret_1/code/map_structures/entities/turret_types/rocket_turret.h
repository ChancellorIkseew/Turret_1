#pragma once
#ifndef ROCKET_TURRET_H
#define ROCKET_TURRET_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/turret/turret.h"


class RocketTurret : public Turret
{
	public:
		
		RocketTurret(int type ,int tileX, int tileY, float curentAngle, short curentDurability);
		RocketTurret(int type);
		~RocketTurret() = default;

		void shooting() override final;
		
		bool needAmoo() override final;
		void takeAmoo(int resType) override final;
		int getAmooType() override final;
		
		void draw(sf::RenderWindow& window) override final;

};

#endif // ROCKET_TURRET_H
